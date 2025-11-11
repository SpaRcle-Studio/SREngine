//
// Created by Monika on 15.10.2025.
//

#include <Engine/AI/Network.h>

namespace SpaRcle::AI {
    NeuralNetwork::NeuralNetwork()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    NeuronId NeuralNetwork::AddNeuron() {
        SR_TRACY_ZONE;
        return m_neurons.Add(Neuron());
    }

    void NeuralNetwork::RemoveNeuron(NeuronId id) {
        SR_TRACY_ZONE;

        m_synapsesCount -= m_neurons.At(id).inputSynapses.size();
        m_synapsesCount -= m_neurons.At(id).outputSynapses.size();

        m_neurons.RemoveByIndex(id);
    }

    void NeuralNetwork::ConnectNeurons(NeuronId from, NeuronId to) {
        SR_TRACY_ZONE;

        m_neurons.At(from).outputSynapses[to] = Synapse();
        m_neurons.At(to).inputSynapses[from] = Synapse();

        ++m_synapsesCount;
    }

    void NeuralNetwork::Tick(float_t dt) {
        SR_TRACY_ZONE;

        m_neurons.ForEach([dt](NeuronId, Neuron& neuron) {
            neuron.Update(dt);
        });

        m_neurons.ForEach([this](NeuronId, Neuron& neuron) {
            neuron.Propagate(*this);
        });
    }

    Neuron& NeuralNetwork::GetNeuron(NeuronId id) {
        return m_neurons.At(id);
    }

    NeuralNetwork::Ptr NeuralNetwork::GenerateNetwork(uint32_t inputCount, uint32_t outputCount, const std::vector<uint32_t>& hiddenLayers, float_t distance) {
        SR_TRACY_ZONE;

        auto&& pNetwork = NeuralNetwork::MakeShared();
        std::vector<NeuronId> previousLayer;

        auto placeLayerAsCenteredGrid = [&](uint32_t count, float_t layerY, std::vector<NeuronId>& outIds) {
            outIds.clear();
            if (count == 0) return;

            // вычисляем количество столбцов/строк для "квадратной" раскладки
            uint32_t cols = static_cast<uint32_t>(std::ceil(std::sqrt(static_cast<float>(count))));
            uint32_t rows = static_cast<uint32_t>(std::ceil(static_cast<float>(count) / static_cast<float>(cols)));

            // смещения для центрирования
            float_t totalWidth  = (cols > 1) ? static_cast<float_t>(cols - 1) * distance : 0.0f;
            float_t totalDepth  = (rows > 1) ? static_cast<float_t>(rows - 1) * distance : 0.0f;
            float_t startX = - totalWidth * 0.5f;
            float_t startZ = - totalDepth * 0.5f;

            for (uint32_t i = 0; i < count; ++i) {
                uint32_t col = i % cols;
                uint32_t row = i / cols; // integer division

                float_t x = startX + static_cast<float_t>(col) * distance;
                float_t y = layerY;
                float_t z = startZ + static_cast<float_t>(row) * distance;

                NeuronId neuronId = pNetwork->AddNeuron();
                auto& neuron = pNetwork->GetNeuron(neuronId);
                neuron.position = SR_MATH_NS::FVector3(x, y, z);

                outIds.push_back(neuronId);
            }
        };

        // входной слой — индекс слоя 0 (ниже всех)
        placeLayerAsCenteredGrid(inputCount, 0.0f, previousLayer);

        // скрытые слои — индекс 1..hiddenLayers.size()
        for (size_t layerIdx = 0; layerIdx < hiddenLayers.size(); ++layerIdx) {
            std::vector<NeuronId> currentLayer;
            float_t layerY = static_cast<float_t>(layerIdx + 1) * distance;
            placeLayerAsCenteredGrid(hiddenLayers[layerIdx], layerY, currentLayer);

            // Подключение: каждый нейрон current <- все нейроны previous
            for (auto neuronId : currentLayer) {
                for (auto prevNeuronId : previousLayer) {
                    pNetwork->ConnectNeurons(prevNeuronId, neuronId);
                }
            }

            previousLayer = std::move(currentLayer);
        }

        // выходной слой — индекс hiddenLayers.size() + 1 (вверху)
        {
            std::vector<NeuronId> outputLayer;
            float_t layerY = static_cast<float_t>(hiddenLayers.size() + 1) * distance;
            placeLayerAsCenteredGrid(outputCount, layerY, outputLayer);

            for (auto neuronId : outputLayer) {
                for (auto prevNeuronId : previousLayer) {
                    pNetwork->ConnectNeurons(prevNeuronId, neuronId);
                }
            }
        }

        return pNetwork;
    }

    void Neuron::Receive(float_t value) {
        if (refractoryTime <= 0.0) { // не принимает сигнал, если “отдыхает”
            inputCurrent += value;
        }
    }

    void Neuron::Update(float_t dt) {
        /// V_rest = 0, τ = 10 утечка
        const float_t tau = 10.0;
        const float_t rest = 0.0;
        const float_t input = inputCurrent; // накопленное от Receive()

        if (refractoryTime > 0.0f) {
            refractoryTime -= dt;
            potential = rest;
            activation = 0.0f;
            inputCurrent = 0.0f;  // пока отдыхает, ничего не интегрирует
            return;
        }

        // Утечка и интеграция
        potential += ((- (potential - rest)) / tau + input) * dt;
        inputCurrent = 0.0f;

        if (potential >= threshold) {
            fired = true;
            activation = 1.0f;
            potential = rest; // сброс
            refractoryTime = 2.0f; // мс условные
        }
        else {
            fired = false;
            activation *= 0.9f; // постепенное затухание
        }
    }

    void Neuron::Propagate(NeuralNetwork& network) {
        if (!fired) {
            return;
        }

        for (auto& [id, syn] : outputSynapses) {
            const auto signal = activation * syn.weight;
            network.GetNeuron(id).Receive(signal);
        }
    }
}
