//
// Created by Monika on 15.10.2025.
//

#ifndef SR_ENGINE_AI_NN_MODEL_H
#define SR_ENGINE_AI_NN_MODEL_H

#include <Engine/AI/Network.h>

#include <Utils/ECS/Component.h>

namespace SR_CORE_NS::AI {
    namespace Details {
        struct Neuron {
            double activation = 0.0;
            std::unordered_map<int, double> connections; // neuron_id -> weight
        };

        struct Network {
            std::vector<Neuron> neurons;
            std::vector<int> lastActivePath;

            void reward(int targetNeuron, double factor = 0.1) {
                for (int id : lastActivePath) {
                    if (neurons[id].connections.count(targetNeuron)) {
                        neurons[id].connections[targetNeuron] += factor;
                        if (neurons[id].connections[targetNeuron] > 1.0)
                            neurons[id].connections[targetNeuron] = 1.0;
                    } else {
                        // если связи нет, создаём маленькую
                        connect(id, targetNeuron, factor);
                    }
                }
            }

            void punish(double factor = 0.1) {
                for (int id : lastActivePath) {
                    for (auto& [to, weight] : neurons[id].connections) {
                        weight -= factor;
                        if (weight < 0.0) weight = 0.0;
                    }
                }
            }

            int addNeuron() {
                neurons.emplace_back();
                return neurons.size() - 1;
            }

            void connect(int from, int to, double weight = 0.1) {
                neurons[from].connections[to] = weight;
            }

            void propagate(int from) {
                for (auto& [to, weight] : neurons[from].connections) {
                    neurons[to].activation += neurons[from].activation * weight;
                }
            }

            void resetActivations() {
                for (auto& n : neurons) n.activation = 0.0;
            }
        };
    }

    /// @category(AI)
    class NNModelComponent : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Awake() override;
        void Update(float_t dt) override;

        SR_NODISCARD bool ExecuteInEditMode() const override { return true; }
        bool IsUpdatable() const noexcept override { return true; }

        void Send();
        void Reward();
        void Punish();

    private:
        /// @property @onChanged(Send)
        bool m_send = false;
        /// @property
        bool m_tick = false;
        /// @property @onChanged(Reward)
        bool m_reward = false;
        /// @property @onChanged(Punish)
        bool m_punish = false;
        /// @property
        SR_UTILS_NS::String m_text;
        /// @property
        SR_UTILS_NS::String m_output;

        //Details::Network m_network;

        SpaRcle::AI::NeuralNetwork::Ptr m_network;

        std::vector<int> m_inputNeurons;
        std::vector<int> m_outputNeurons;

    };
}

#endif //SR_ENGINE_AI_NN_MODEL_H
