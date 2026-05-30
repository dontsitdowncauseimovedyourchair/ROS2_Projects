//
// Created by ale on 30/05/26.
//

#include <rclcpp/rclcpp.hpp>
#include <example_interfaces/srv/add_two_ints.hpp>

using namespace std::chrono_literals;

class AddTwoIntsClientsNode : public rclcpp::Node {
public:
    AddTwoIntsClientsNode(): Node("add_two_ints_client") {
        client_ = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
    }

    void callAddTwoInts() {
        while (!client_->wait_for_service(1s))
        {
            RCLCPP_WARN(this->get_logger(), "Waiting for service to flip....");
        }
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = 7;
        request->b = 12;

        client_->async_send_request(request, std::bind(&AddTwoIntsClientsNode::callbackCallAddTwoInts, this, std::placeholders::_1));
    }

private:
    rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedPtr client_;

    void callbackCallAddTwoInts(rclcpp::Client<example_interfaces::srv::AddTwoInts>::SharedFuture future) {
        auto response = future.get();
        RCLCPP_INFO(this->get_logger(), "Sum %d", (int)response->sum);
    }
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoIntsClientsNode>();
    node->callAddTwoInts();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}