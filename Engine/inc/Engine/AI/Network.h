//
// Created by Monika on 15.10.2025.
//

#ifndef SR_ENGINE_AI_NETWORK_H
#define SR_ENGINE_AI_NETWORK_H

#include <Engine/macros.h>

#include <Utils/Types/ObjectPool.h>
#include <Utils/Types/SharedPtr.h>

namespace SpaRcle::AI {
    using NeuronId = uint64_t;

    struct Synapse {
        float_t weight = 1.0f;
    };

    class NeuralNetwork;

    struct Neuron {
        float_t threshold = 1.0;
        float_t inputCurrent = 0.0;
        float_t activation = 0.0;
        float_t refractoryTime = 0.0;
        float_t potential = 0.0;
        float_t weight = 1.0f;
        bool fired = false;
        SR_MATH_NS::FVector3 position;
        std::unordered_map<NeuronId, Synapse> inputSynapses; /// TODO: дублирование информации, нужно исправить.
        std::unordered_map<NeuronId, Synapse> outputSynapses;

        void Propagate(NeuralNetwork& network);
        void Receive(float_t signal);
        void Update(float_t dt);

    };

    class NeuralNetwork : public SR_HTYPES_NS::SharedPtr<NeuralNetwork> {
        using Super = SR_HTYPES_NS::SharedPtr<NeuralNetwork>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<NeuralNetwork>;

    public:
        NeuralNetwork();

        SR_NODISCARD static NeuralNetwork::Ptr GenerateNetwork(uint32_t inputCount, uint32_t outputCount, const std::vector<uint32_t>& hiddenLayers, float_t distance = 1.0f);

        void Tick(float_t dt);

        SR_NODISCARD Neuron& GetNeuron(NeuronId id);

        SR_NODISCARD uint64_t GetSynapsesCount() const { return m_synapsesCount; }
        SR_NODISCARD uint64_t GetNeuronsCount() const { return m_neurons.GetAliveCount(); }

        SR_NODISCARD NeuronId AddNeuron();
        void RemoveNeuron(NeuronId id);

        void ConnectNeurons(NeuronId from, NeuronId to);

        void ForEachNeuron(const std::function<void(NeuronId, Neuron&)>& func) {
            SR_TRACY_ZONE;
            m_neurons.ForEach(func);
        }

    private:
        uint64_t m_synapsesCount = 0;
        SR_HTYPES_NS::ObjectPool<Neuron, NeuronId> m_neurons;

    };
}

#endif //SR_ENGINE_AI_NETWORK_H
