FROM ubuntu

RUN apt-get update && apt-get -y install cmake

WORKDIR app/
COPY VirtualAllocReader/. ./VirtualAllocReader/
COPY shm_lib/. ./shm_lib/

WORKDIR VirtualAllocReader/
RUN ["/bin/bash", "-c", "cmake -S. -Bbuild -DBUILD_TESTING=OFF"]
RUN ["/bin/bash", "-c", "cmake --build build --config Release"]
ENTRYPOINT ["/bin/bash", "-c", "./build/VirtualAllocReader"]
