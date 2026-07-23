//
// Created by Monika on 15.10.2025.
//

#include <Engine/AI/NeuralNetwork/NNModel.h>

#include <Codegen/NNModel.generated.hpp>

namespace SR_CORE_NS::AI {
    namespace Details {
        int letterToIndex(char c) {
            if (c >= 'a' && c <= 'z') {
                return (c - 'a') + 1;
            }
            return 0;
        }

        char indexToLetter(int idx) {
            if (idx == 0) return ' ';
            if (idx >= 1 && idx <= 26) {
                return 'a' + (idx - 1);
            }
            return ' ';
        }

        char predictNext(Network& net, const std::vector<int>& inputNeurons) {
            double maxActivation = -1.0;
            int maxIdx = 0;
            for (int i = 0; i < inputNeurons.size(); ++i) {
                double act = net.neurons[inputNeurons[i]].activation;
                if (act > maxActivation) {
                    maxActivation = act;
                    maxIdx = i;
                }
            }
            return char('a' + maxIdx);
        }

        void FeedLetter(Network& net, char c, std::vector<int>& activePath, std::vector<double>& assocActivation, const std::vector<int>& inputNeurons) {
            int idx = letterToIndex(c);

            // сбрасываем только входные нейроны
            for (int i = 0; i < inputNeurons.size(); ++i)
                net.neurons[inputNeurons[i]].activation = 0.0;

            net.neurons[inputNeurons[idx]].activation = 1.0;
            activePath.clear();
            activePath.push_back(inputNeurons[idx]);

            // распространение сигнала через все нейроны
            for (int i = 0; i < net.neurons.size(); ++i) {
                // добавляем предыдущую ассоциативную активацию
                assocActivation.resize(SR_MAX(assocActivation.size(), net.neurons.size()));
                net.neurons[i].activation += assocActivation[i];
                net.propagate(i);

                if (net.neurons[i].activation > 0.5)
                    activePath.push_back(i);
            }

            // проверка на новые комбинации → создание ассоциативного нейрона
            bool found = false;
            for (auto& n : net.neurons) {
                double overlap = 0.0;
                for (int id : activePath)
                    if (n.connections.count(id)) overlap += n.connections[id];

                if (overlap > 0.3) { // порог совпадения
                    found = true;
                    break;
                }
            }

            if (!found) {
                int newAssoc = net.addNeuron();
                for (int id : activePath)
                    net.connect(id, newAssoc, 0.1);

                activePath.push_back(newAssoc);
            }

            // сохраняем текущую активность для ассоциативных нейронов (контекст)
            assocActivation.resize(SR_MAX(assocActivation.size(), net.neurons.size()));
            for (int i = 0; i < net.neurons.size(); ++i)
                assocActivation[i] = net.neurons[i].activation;
        }

        void FeedLetter(Network& net, char c, const std::vector<int>& inputNeurons) {
            std::vector<int> activePath;
            std::vector<double> assocActivation;
            FeedLetter(net, c, activePath, assocActivation, inputNeurons);
        }

        void FeedText(Network& net, const std::string& text, const std::vector<int>& inputNeurons) {
            std::string output;
            std::vector<int> activePath; // нейроны для reward/punish

            // буфер текущей активности ассоциативных нейронов (не сбрасываем каждый шаг)
            std::vector<double> assocActivation(net.neurons.size(), 0.0);

            for (char c : text) {
                FeedLetter(net, c, activePath, assocActivation, inputNeurons);

                // предсказываем следующую букву
                char next = predictNext(net, inputNeurons);
                output += next;
            }

            // сохраняем путь для reward/punish
            net.lastActivePath = activePath;

            std::cout << "NNModel::FeedText() : " << output << std::endl;
        }

    }

    void NNModelComponent::Awake() {
        m_inputNeurons.resize(27);
        m_outputNeurons.resize(27);

        m_network = SpaRcle::AI::NeuralNetwork::MakeShared();

        for (auto& neuron : m_inputNeurons) {
            neuron = m_network->AddNeuron();
        }

        for (auto& neuron : m_outputNeurons) {
            neuron = m_network->AddNeuron();
        }

        std::vector<int> hiddenLayer;
        hiddenLayer.resize(100);

        for (auto& neuron : hiddenLayer) {
            neuron = m_network->AddNeuron();
        }

        // полносвязная сеть
        for (auto inputNeuron : m_inputNeurons) {
            for (auto hiddenNeuron : hiddenLayer) {
                m_network->ConnectNeurons(inputNeuron, hiddenNeuron);
            }
        }

        for (auto hiddenNeuron : hiddenLayer) {
            for (auto outputNeuron : m_outputNeurons) {
                m_network->ConnectNeurons(hiddenNeuron, outputNeuron);
            }
        }

        Super::Awake();
    }

    void NNModelComponent::Update(float_t dt) {
        SR_TRACY_ZONE;
        if (m_tick) {
            m_network->Tick(dt);
            m_tick = false;

            m_output.clear();

            for (size_t i = 0; i < m_outputNeurons.size(); ++i) {
                auto&& neuron = m_network->GetNeuron(m_outputNeurons[i]);
                if (neuron.activation > 0.5) {
                    m_output += Details::indexToLetter(i);
                }
            }
        }
    }

    void NNModelComponent::Send() {
        //Details::FeedText(m_network, m_text, m_inputNeurons);

        for (size_t i = 0; i < m_text.size(); ++i) {
            auto&& neuron = m_network->GetNeuron(m_inputNeurons[Details::letterToIndex(m_text[i])]);
            neuron.Receive(5.0);
        }

        m_tick = true;
        Update(1.16666f);

        m_send = false;
    }

    void NNModelComponent::Reward() {
        //for (size_t i = 0; i < m_text.size(); ++i) {
        //    char c = m_text[i];
        //    char nextTarget = (i+1 < m_text.size()) ? m_text[i+1] : '.';
        //    int targetIdx = Details::letterToIndex(nextTarget);
        //
        //    FeedLetter(m_network, c, m_inputNeurons); // propagate + ассоц. нейроны
        //    m_network.reward(targetIdx);            // усиливаем правильную букву
        //}
        m_reward = false;
    }

    void NNModelComponent::Punish() {
        //m_network.punish();
        m_punish = false;
    }
}