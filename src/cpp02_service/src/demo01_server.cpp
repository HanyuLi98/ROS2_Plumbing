/* 
需求：编写服务端实现，解析提交的请求数据，将解析的数据相加并相应到客户端。
1.包含头文件；
2.初始化 ROS2 客户端；
3.定义节点类；
  3.1 创建服务端
  3.2 回调函数，解析请求并发送响应
4.调用spin函数，并传入节点对象指针；
5.释放资源。
*/
//1.包含头文件；
#include "rclcpp/rclcpp.hpp"
#include "base_interfaces_demo/srv/add_ints.hpp"

using base_interfaces_demo::srv::AddInts;
using std::placeholders::_1;
using std::placeholders::_2;
//3.定义节点类；
class AddIntsServer: public rclcpp::Node{
public:
    AddIntsServer():Node("addIntsServer_node_cpp"){
        RCLCPP_INFO(this->get_logger(), "服务端节点创建");
        //3.1 创建服务端
        /* 
            模板：服务接口类型
            参数：
                服务话题
                回调函数
            返回值：服务对象指针
        
         */
        server_ = this->create_service<AddInts>("add_ints",std::bind(&AddIntsServer::add,this,_1,_2));
    }
private:
    rclcpp::Service<AddInts>::SharedPtr server_;
    /*  */
    void add(const AddInts::Request::SharedPtr req, const AddInts::Response::SharedPtr res){
    //3.2 回调函数，解析请求并发送响应
        res->sum = req->num1 + req->num2; 
        RCLCPP_INFO(this->get_logger(),"%d + %d = %d", req->num1, req->num2, res->sum);

    }        
};
 
int main(int argc, char const *argv[])
{
    //2.初始化 ROS2 客户端； 
    rclcpp::init(argc,argv);
    //4.调用spin函数，并传入节点对象指针；  
    rclcpp::spin(std::make_shared<AddIntsServer>());  
    //5.释放资源。 
    rclcpp::shutdown();
    return 0;
}