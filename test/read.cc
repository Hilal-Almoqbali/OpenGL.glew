#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

struct ShadderSource
{
    std::string vertexSource;
    std::string fragmentSource;
};
static ShadderSource ParseShader(std::string filePath);


int main(void)
{
    ShadderSource src = ParseShader("./tringle0.shader");
    std::cout<< src.fragmentSource<<std::endl;
    std::cout<< src.vertexSource<<std::endl;

}


static ShadderSource ParseShader(std::string filePath)
{
    std::ifstream stream(filePath);

    enum class ShaderType
    {
        NONE =-1,VERTEX = 0,FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream,line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
            {
                //set mode to vertex
                type = ShaderType::VERTEX;
            }
            if(line.find("fragment") != std::string::npos)
            {
                //set mode to fragment
                type = ShaderType::FRAGMENT;
            }
            else
            {
                ss[(int)type] << line <<"\n";
            }
        }
    }
    return {ss[0].str(),ss[1].str()};
}