FROM mcr.microsoft.com/devcontainers/cpp:bookworm

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# Update your package list
RUN apt update
# Install the Boost development libraries
RUN apt install -y libboost-all-dev