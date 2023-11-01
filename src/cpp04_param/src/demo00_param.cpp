/* 
需求：演示参数API使用。
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类； 
  3.1 参数对象创建
  3.2 参数对象解析（获取键，值，将值转换成字符串...）
4.调用spin函数，并传入节点对象指针；
5.释放资源。
*/
//1.包含头文件；
#include "rclcpp/rclcpp.hpp"
//3.定义节点类；
class MyPara: public rclcpp::Node{
public:
    MyPara():Node("my_para_node_cpp"){
    RCLCPP_INFO(this->get_logger(), "参数API使用");
    //3.1 参数对象创建
    rclcpp::Parameter p1("car_name", "tiger");
    rclcpp::Parameter p2("height", 1.68);
    rclcpp::Parameter p3("wheels", 4);
    //3.2 参数对象解析（获取键，值，将值转换成字符串...）
    //解析值
    RCLCPP_INFO(this->get_logger(), "car_name = %s", p1.as_string().c_str());
    RCLCPP_INFO(this->get_logger(), "height = %.2f", p2.as_double());
    RCLCPP_INFO(this->get_logger(), "wheels = %ld", p3.as_int());

    //获取参数键
    RCLCPP_INFO(this->get_logger(), "name = %s", p1.get_name().c_str());
    //获取数据类型
    RCLCPP_INFO(this->get_logger(), "type = %s", p1.get_type_name().c_str());
    //str方式打印value
    RCLCPP_INFO(this->get_logger(), "value2string = %s", p2.value_to_string().c_str());

    }
};
 
int main(int argc, char const *argv[])
{
    //2.初始化 ROS2 客户端； 
    rclcpp::init(argc,argv);
    //4.调用spin函数，并传入节点对象指针；  
    rclcpp::spin(std::make_shared<MyPara>());  
    //5.释放资源。 
    rclcpp::shutdown();
    return 0;
}