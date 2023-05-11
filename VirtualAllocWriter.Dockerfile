FROM ubuntu

RUN apt-get update && apt-get -y install cmake

WORKDIR app/
COPY VirtualAllocWriter/. ./VirtualAllocWriter/
COPY shm_lib/. ./shm_lib/

WORKDIR VirtualAllocWriter/
RUN ["/bin/bash", "-c", "cmake -S. -Bbuild -DBUILD_TESTING=OFF"]
RUN ["/bin/bash", "-c", "cmake --build build --config Release"]
ENTRYPOINT ["/bin/bash", "-c", "./build/VirtualAllocWriter"]
