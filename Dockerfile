FROM centos:7

WORKDIR /root

RUN yum -y update && \
	yum -y groupinstall "Development Tools" && \
	yum install -y vim make ncurses-devel

ENV LANG C.UTF-8

COPY src /root/