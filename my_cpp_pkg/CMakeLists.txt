cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(my_robot_interfaces REQUIRED)

add_executable(my_node src/my_node.cpp)
add_executable(robot_news_station src/robot_news_station.cpp)
add_executable(smartphone src/smartphone.cpp)
add_executable(number_publisher src/number_publisher.cpp)
add_executable(num_subpub src/num_subpub.cpp)
add_executable(add_two_ints_server src/add_two_ints_server.cpp)
add_executable(add_two_ints_client_no_oop src/add_two_ints_client_no_oop.cpp)
add_executable(add_two_ints_client src/add_two_ints_client.cpp)
add_executable(hw_status_publisher src/hardware_status_publisher.cpp)

ament_target_dependencies(my_node rclcpp)
ament_target_dependencies(robot_news_station rclcpp example_interfaces)
ament_target_dependencies(smartphone rclcpp example_interfaces)
ament_target_dependencies(number_publisher rclcpp example_interfaces)
ament_target_dependencies(num_subpub rclcpp example_interfaces)
ament_target_dependencies(add_two_ints_server rclcpp example_interfaces)
ament_target_dependencies(add_two_ints_client_no_oop rclcpp example_interfaces)
ament_target_dependencies(add_two_ints_client rclcpp example_interfaces)
ament_target_dependencies(hw_status_publisher rclcpp example_interfaces my_robot_interfaces)


install(TARGETS
  my_node
  robot_news_station
  smartphone
  number_publisher
  num_subpub
  add_two_ints_server
  add_two_ints_client_no_oop
  add_two_ints_client
  hw_status_publisher

  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
