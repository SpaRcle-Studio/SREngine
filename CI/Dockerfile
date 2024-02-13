FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y wget sudo
RUN wget -qO- https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo tee /etc/apt/trusted.gpg.d/lunarg.asc
RUN sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-jammy.list http://packages.lunarg.com/vulkan/lunarg-vulkan-jammy.list
RUN apt-get update
RUN apt-get install -y neofetch vulkan-sdk vulkan-tools build-essential \ 
	git cmake net-tools gdb clang xcb libxcb-xkb-dev x11-xkb-utils \
	libx11-xcb-dev libxkbcommon-x11-dev libxtst-dev libxcb-ewmh-dev \
	binutils-dev libgtk-3-0 cmake build-essential libgtk-3-dev libx11-dev \
	libxcb-randr0-dev libxcb-cursor-dev libxcb-keysyms1-dev \
	librust-xcb+xfixes-dev libxcb-util-dev
