FROM ubuntu:18.04
# Set the working directory in the container
WORKDIR /reactFrontend

# Install any needed packages specified in package.json
COPY package*.json ./
RUN npm install

COPY . .

# Install needed tools for React.js
RUN npm run install

# Use an official gcc image as a parent image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /backend

# Install crow and nlohmann/json for C++
RUN apt-get update && \
    apt-get install -y cmake && \
    apt-get install -y libboost-cpp-dev && \
    git clone --depth=1 https://github.com/ipkn/crow.git && \
    cd crow && mkdir build && cd build && \
    cmake .. && make && make install && \
    cd ../.. && rm -rf crow && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Build your C++ application
RUN mkdir build &&\
    cd build &&\
    cmake .. &&\
    cd adaptive-radix-tree &&\
    make &&\
    cd .. &&\
    make \
# Run your application
CMD ["./crow_test"]