FROM node:18-slim AS build

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
# CMD ["npm", "run", "preview"]

FROM nginx
COPY ./nginx/nginx.conf /etc/nginx/conf.d/default.conf
COPY --from=build /usr/src/dist /usr/share/nginx/html

EXPOSE 8080
CMD ["nginx", "-g", "daemon off;"]
