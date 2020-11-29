FROM node:lts

WORKDIR /tema2-sprc

COPY tsconfig.json ./

COPY package*.json ./

RUN npm install

COPY . .

EXPOSE 3000

CMD ["npm", "run", "dev"]
