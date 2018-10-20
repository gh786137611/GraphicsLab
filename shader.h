#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <GL/glew.h>

using namespace std;


class Shader
{
public:
        Shader(const string&vfile, const string &ffile)
        {
                unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
                {
                        string source = read_file(vfile);
                        const char * p = source.c_str();
                        glShaderSource(vertex_shader, 1, &p, nullptr);
                        glCompileShader(vertex_shader);
                        int status;
                        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &status);
                        if (!status) {
                                char log[512];
                                int length;
                                glGetShaderInfoLog(vertex_shader, 511, &length, log);
                                log[511] = 0;
                                cout << log<<endl;
                                return;
                        }
                }

                unsigned frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
                {
                        string source = read_file(ffile);
                        const char * p = source.c_str();
                        glShaderSource(frag_shader, 1, &p, nullptr);
                        glCompileShader(frag_shader);
                        int status;
                        glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &status);
                        if (!status) {
                                char log[512];
                                int length;
                                glGetShaderInfoLog(frag_shader, 511, &length, log);
                                log[511] = 0;
                                cout << log<<endl;
                                return;
                        }
                }

                m_program = glCreateProgram();
                glAttachShader(m_program, vertex_shader);
                glAttachShader(m_program, frag_shader);
                glLinkProgram(m_program);
                glDeleteShader(vertex_shader);
                glDeleteShader(frag_shader);
        }

        int get_attrib_location(const string &name)
        {
                auto it = m_location.find(name);
                if (m_location.end() != it)
                        return it->second;
                else{
                        return find_attrib_location(name);
                }

        }
        int get_uniform_location(const string &name)
        {
                auto it = m_location.find(name);
                if (m_location.end() != it)
                        return it->second;
                else{
                        return find_uniform_location(name);
                }

        }

        void use()
        {
                glUseProgram(m_program);
        }
        void unuse()
        {
                glUseProgram(0);
        }
private:
        static string read_file(const string &file)
        {
                string line, ret;
                ifstream fin(file);
                if (fin){
                        while (getline(fin, line)) {
                                if (fin)
                                        ret += line + "\n";
                                else
                                        ret += line;
                        }
                }else {
                        cerr <<"failed to open file:"<<file <<endl;
                }
                return ret;
        }

        int find_attrib_location(const string & name)
        {
                int loc = glGetAttribLocation(m_program, name.c_str());
                m_location[(name)] = loc;
                return loc;
        }

        int find_uniform_location(const string & name)
        {
                int loc = glGetUniformLocation(m_program, name.c_str());
                m_location[(name)] = loc;
                return loc;
        }

private:
        unsigned m_program;
        map<string, int> m_location;
};

#endif
