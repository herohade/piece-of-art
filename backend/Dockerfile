FROM ubuntu:latest

WORKDIR /usr/src

RUN apt-get update -y && \
    apt-get install -y build-essential libtcmalloc-minimal4 && \
    ln -s /usr/lib/libtcmalloc_minimal.so.4 /usr/lib/libtcmalloc_minimal.so && \
    apt-get install -y cmake && \
    apt-get install -y libboost-all-dev && \
    apt-get install -y wget && \
    apt-get install -y git && \
    apt-get install -y openssl && \
    apt-get install -y python3 && \
    apt-get upgrade -y cmake && \
    # git clone https://github.com/CrowCpp/Crow.git && \
    # cd Crow && mkdir build && cd build && \
    # cmake .. -DCROW_BUILD_EXAMPLES=OFF -DCROW_BUILD_TESTS=OFF && \
    # make install && cd /usr/src
    git clone https://github.com/CrowCpp/Crow.git && \
    cd Crow && cd scripts && \
    ./merge_all.py ../include crow_all.h && \
    cd /usr/src

COPY . .

# Build your C++ application
RUN mkdir build && \
    cd build && \
    cmake .. && \
    # cd adaptive-radix-tree && \
    # make && \
    # cd .. &&\
    make

# Run your application
CMD ["/usr/src/build/crow_test"]
