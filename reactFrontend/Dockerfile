FROM node:18-slim

WORKDIR /usr/src

COPY package*.json ./

RUN npm install

# copy all files from current directory to working directory
COPY * .
# copy /src and /public directories to working directory
COPY src ./src
COPY public ./public

# npm run build
RUN npm run build

# npm run preview
CMD ["npm", "run", "preview"]