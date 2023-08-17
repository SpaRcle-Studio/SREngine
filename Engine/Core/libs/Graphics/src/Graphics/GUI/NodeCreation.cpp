//
// Created by Monika on 15.08.2023.
//

#include <Graphics/GUI/NodeCreation.h>
#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Utils/SRLM/LogicalMachine.h>

namespace SR_GRAPH_GUI_NS {
    Node* CreateNode(const SR_MATH_NS::FVector2& pos, uint64_t identifier) {
        auto&& pNode = new SR_GRAPH_GUI_NS::Node();
        auto&& node = *pNode;

        node.SetPosition(pos);
        node.SetIdentifier(identifier);
        node.SetType(SR_GRAPH_GUI_NS::NodeType::Simple);

        switch (identifier) {
            case SR_SRLM_NS::NODE_BOOL_CONDITION: {
                node.SetName("Condition")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Flow)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddOutput("True", SR_GRAPH_GUI_NS::PinType::Flow)
                    .AddOutput("False", SR_GRAPH_GUI_NS::PinType::Flow)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_BOOL_AND: {
                node.SetName("And")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Bool)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_BOOL_OR: {
                node.SetName("Or")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Bool)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_BOOL_NOT: {
                node.SetName("Not")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Bool)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_INT_NEGATIVE: {
                node.SetName("-")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Int)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Int)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_INT_TO_FLOAT: {
                node.SetName("Int to Float")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Int)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Float)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_INT_PLUS_INT: {
                node.SetName("+")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Int)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Int)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Int)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_INT_MINUS_INT: {
                node.SetName("-")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Int)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Int)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Int)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_FLOAT_NEGATIVE: {
                node.SetName("-")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Float)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Float)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_FLOAT_TO_INT: {
                node.SetName("Float to Int")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Float)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Int)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_FLOAT_PLUS_FLOAT: {
                node.SetName("+")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Float)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Float)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Float)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_FLOAT_MINUS_FLOAT: {
                node.SetName("-")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Float)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Float)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Float)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_START_PASS: {
                node.SetName("Start Pass")
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Flow)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_END_PASS: {
                node.SetName("End Pass")
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Flow)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_CASCADED_SHADOW_MAP_PASS: {
                node.SetName("Cascaded Shadow Map Pass")
                    .SetType(NodeType::Blueprint)
                    .AddInput(SR_GRAPH_GUI_NS::PinType::Flow)
                    .AddInput("Cascades", SR_GRAPH_GUI_NS::PinType::Int)
                    .AddInput("SplitLambda", SR_GRAPH_GUI_NS::PinType::Float)
                    .AddInput("Near", SR_GRAPH_GUI_NS::PinType::Float)
                    .AddInput("Far", SR_GRAPH_GUI_NS::PinType::Float)
                    .AddInput("Depth", SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddInput("DynamicResizing", SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddInput("Smooth", SR_GRAPH_GUI_NS::PinType::Int)
                    .AddInput("Layers", SR_GRAPH_GUI_NS::PinType::Int)
                    .AddOutput(SR_GRAPH_GUI_NS::PinType::Flow)
                ;
                break;
            }
            case SR_SRLM_NS::NODE_FRAME_BUFFER_SETTINGS: {
                node.SetName("Frame Buffer Settings")
                    .SetType(NodeType::Blueprint)
                    .AddInput("Size", SR_GRAPH_GUI_NS::PinType::Struct, SR_SRLM_NS::DATA_TYPE_INT_VECTOR2)
                    .AddInput("Pre Scale", SR_GRAPH_GUI_NS::PinType::Struct, SR_SRLM_NS::DATA_TYPE_FLOAT_VECTOR2)
                    .AddInput("Depth Enabled", SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddInput("DynamicResizing", SR_GRAPH_GUI_NS::PinType::Bool)
                    .AddInput("Smooth", SR_GRAPH_GUI_NS::PinType::Int)
                    .AddInput("Layers", SR_GRAPH_GUI_NS::PinType::Int)
                    .AddOutput("Result", SR_GRAPH_GUI_NS::PinType::Struct, SR_SRLM_NS::DATA_TYPE_FRAME_BUFFER_SETTINGS)
                ;
                break;
            }
            default:
                SRHalt("Invalid identifier");
                break;
        }

        /*
         *         <FramebufferSettings DynamicResizing="true" DepthEnabled="true" SmoothSamples="1">
            <Size X="0" Y="0"/>
            <PreScale X="1.0" Y="1.0"/>
            <Depth Format="Auto" ClearValue="1.0"/>
            <Layer Format="RGBA8_UNORM" R="0.0" G="0.0" B="0.0" A="1.0"/>
        </FramebufferSettings>
         */

        return pNode;
    }
}