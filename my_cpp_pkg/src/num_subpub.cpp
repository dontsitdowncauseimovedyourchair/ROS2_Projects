//
// Created by ale on 26/05/26.
//

#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>
#include <example_interfaces/srv/set_bool.hpp>

class NumSubPubNode : public rclcpp::Node {
public:
    NumSubPubNode() : Node("num_sub_pub"), count_(0u)  {
        publisher_ = rclcpp::create_publisher<example_interfaces::msg::Int64>(this, "number_count", 10);
        subscription_ = this->create_subscription<example_interfaces::msg::Int64>("number", 10, std::bind(&NumSubPubNode::habemus_number, this, std::placeholders::_1));
        server_ = this->create_service<example_interfaces::srv::SetBool>("reset_counter", std::bind(&NumSubPubNode::callbackResetService, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(), "Empezando a Chambear en contacion");
    }

private:
    unsigned long long count_ = 0;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscription_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;

    void habemus_number(const example_interfaces::msg::Int64::SharedPtr in) {
        RCLCPP_INFO(this->get_logger(), "Recibido: %ld", in->data);
        auto msg = example_interfaces::msg::Int64();
        msg.data = count_++;
        publisher_->publish(msg);
    }

    void callbackResetService(const example_interfaces::srv::SetBool::Request::SharedPtr request, const example_interfaces::srv::SetBool::Response::SharedPtr response) {
        if (request->data) {
            count_ = 0;
            response->success = true;
            response->message = "Counter has lost its memory.";
        } else
        {
            response->success = false;
            response->message = "Counter untouched";
        }

    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumSubPubNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}