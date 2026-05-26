//
// Created by ale on 26/05/26.
//

#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/msg/int64.hpp>

class NumSubPubNode : public rclcpp::Node {
public:
    NumSubPubNode() : Node("num_sub_pub"), count_(0u)  {
        publisher_ = rclcpp::create_publisher<example_interfaces::msg::Int64>(this, "number_count", 10);
        subscription_ = this->create_subscription<example_interfaces::msg::Int64>("number", 10, std::bind(&NumSubPubNode::habemus_number, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Empezando a Chambear en contacion");
    }

private:
    unsigned long long count_ = 0;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscription_;

    void habemus_number(const example_interfaces::msg::Int64::SharedPtr in) {
        RCLCPP_INFO(this->get_logger(), "Recibido: %ld", in->data);
        auto msg = example_interfaces::msg::Int64();
        msg.data = count_++;
        publisher_->publish(msg);
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumSubPubNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}