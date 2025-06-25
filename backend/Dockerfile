# Official Node.js v20 image from Docker Hub
FROM node:20

# Set working dir for all commands
WORKDIR /app

# Copy package files and install dependencies
COPY package*.json ./
RUN npm install

# Copy rest of backend folder
COPY . .

# Expose port that Express will use
EXPOSE 3000

# Start the server >:P
CMD ["node", "server.js"]
