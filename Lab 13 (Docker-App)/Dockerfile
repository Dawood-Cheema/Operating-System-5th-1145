FROM node:lts-alpine3.23

COPY public .
COPY index.js .
COPY package.json .
RUN npm i
CMD ["node", "index.js"]