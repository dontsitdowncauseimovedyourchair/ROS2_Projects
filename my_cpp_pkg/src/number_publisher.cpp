//
// Created by ale on 26/05/26.
//

#include <example_interfaces/msg/int64.hpp>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class NumberCounterNode : public rclcpp::Node {
public:
    NumberCounterNode() : Node("number_publisher"), num(0) {
        publisher_ = rclcpp::create_publisher<example_interfaces::msg::Int64>(this, "number", 10);
        timer_ = this->create_wall_timer(1s, std::bind(&NumberCounterNode::publishNumber, this));
        RCLCPP_INFO(this->get_logger(), "ATENCIÓN!! NÚMERO PUBLICANDO");
    }

private:
    void publishNumber() {
        auto msg = example_interfaces::msg::Int64();
        msg.data = num++;
        publisher_->publish(msg);
    }

    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    unsigned long long num = 0;
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounterNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}