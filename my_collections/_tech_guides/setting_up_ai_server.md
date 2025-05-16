---
layout: default
title: Setting Up an AI Server with Ollama and Docker
date: 2025-02-10
domain: Guides
system: Ubuntu
published: false
---

# Setting Up an AI Server with Ollama and Docker

---

Date: 2025-02-10  
OS/Distro: Ubuntu 24.04.1 LTS  
Resources used:  
- [ollama](https://ollama.com/)  
- [Install Docker with apt](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository)  
- [Quick Start With Docker](https://docs.openwebui.com/#quick-start-with-docker-)

---

## Install Ollama
1. Install using curl
    
    ```bash
    $ curl -fsSL https://ollama.com/install.sh | sh
    ```

2. Verify it was successful

    ```bash
    $ ollama --version
    ```

### Pull a model and test it
3. I chose deepseek-r1:1.5b

    ```bash
    $ ollama pull deepseek-r1:1.5b
    ```

4. Test it was successful

    ```bash
    $ ollama run deepseekr1:1.5b
    ```

## Install Docker
I followed the instruction to install Docker with apt to the letter. Here they are.

1. Set up Docker's `apt` repository.

    ```bash
    # Add Docker's official GPG key:
    sudo apt-get update
    sudo apt-get install ca-certificates curl
    sudo install -m 0755 -d /etc/apt/keyrings
    sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
    sudo chmod a+r /etc/apt/keyrings/docker.asc

    # Add the repository to Apt sources:
    echo \
      "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
      $(. /etc/os-release && echo "${UBUNTU_CODENAME:-$VERSION_CODENAME}") stable" | \
      sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
    sudo apt-get update
    ```

2. Install the Docker packages.

    ```bash
    sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
    ```

3. Verify that the installation is successful.

    ```bash
    sudo docker run hello-world
    ```

## Get Things Running
1. Run A New Docker Image and Download Open WebUI

    ```bash
    docker run -d -p 3000:8080 -v ollama:/root/.ollama -v open-webui:/app/backend/data --name open-webui --restart always ghcr.io/open-webui/open-webui:ollama
    ```

2. In a browsers address bar, type `http://localhost:3000/auth` in the address bar. You will be prompted to create a username and password.
3. Done! You have an active docker container "serving" you access to a LLM running locally on your machine.
