//
// Created by ale on 05/04/26.
//

#include <rclcpp/rclcpp.hpp>

class MyNode : public rclcpp::Node {
public:
    MyNode() : Node("cpp_node"), _counter(0) {
        RCLCPP_INFO(this->get_logger(), "Hola papus OOP");
        _timer = this->create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timer_callback, this));
    }
private:
    size_t _counter;
    rclcpp::TimerBase::SharedPtr _timer;

    void timer_callback() {
        RCLCPP_INFO(this->get_logger(), "Hello papus part %lu", _counter);
        _counter++;
    }

};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
}