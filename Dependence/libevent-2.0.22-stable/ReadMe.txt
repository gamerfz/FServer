========================================================================
    静态库：libevent-2.0.22-stable 项目概述
========================================================================

应用程序向导已为您创建了此 libevent-2.0.22-stable 库项目。

没有为此项目创建源文件。


libevent-2.0.22-stable.vcxproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

libevent-2.0.22-stable.vcxproj.filters
    这是使用“应用程序向导”生成的 VC++ 项目筛选器文件。它包含有关项目文件与筛选器之间的关联信息。在 IDE 中，通过这种关联，在特定节点下以分组形式显示具有相似扩展名的文件。例如，“.cpp”文件与“源文件”筛选器关联。

/////////////////////////////////////////////////////////////////////////////
其他注释:

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////

  此项目用于libevent在windows下的编译
  具体步骤如下:
  1新建空项目,可直接添加新项目,将目录指向libevent-2.0.22-stable文件夹所在目录,并将项目名字设置为libevent-2.0.22-stable
  2添加头文件,接将libevent-2.0.22-stable\include\event2中的头文件包含到项目中
  3添加源文件,将libevent-2.0.22-stable目录下.c文件添加到项目中
  4删除不相关的文件,由于添加的文件中包含部分linux相关代码,需要将这些文件从项目中移除内容包括
  (arc4random.c bufferevent_openssl.c devpoll.c epoll.c epoll_sub.c evport.c evthread_pthread.c kqueue.c poll.c select.c)
  5附加包含目录
  $(SolutionDir)\Dependence\libevent-2.0.22-stable;
  $(SolutionDir)\Dependence\libevent-2.0.22-stable\compat;
  $(SolutionDir)\Dependence\libevent-2.0.22-stable\include;
  $(SolutionDir)\Dependence\libevent-2.0.22-stable\WIN32-Code;
  %(AdditionalIncludeDirectories)
  6附加依赖项
  Ws2_32.lib
  7设置编译输出目录