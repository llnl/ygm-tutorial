FROM ghcr.io/llnl/radiuss:gcc-14-ubuntu-24.04

ARG USER=tutorial
ARG OPENVSCODE_VERSION=v1.109.5

# Switch to root for installations
USER root

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
 && apt-get install -y --no-install-recommends \
    supervisor \
    clangd-19 \
    clang-tidy-19 \
    openmpi-bin \
    libopenmpi-dev \
    python3-venv \
 && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/clangd clangd /usr/bin/clangd-19 100
RUN update-alternatives --install /usr/bin/clang-tidy clang-tidy /usr/bin/clang-tidy-19 100

RUN pip3 install --break-system-packages --no-cache-dir pyarrow

RUN useradd --create-home --home-dir /home/${USER} --shell /bin/bash ${USER}

ENV HOME=/home/${USER}

# Install openvscode-server. The stable symlink at /opt/openvscode-server
# means supervisord.conf doesn't need to know the exact version.
WORKDIR /opt/archives
RUN curl -fL \
        "https://github.com/gitpod-io/openvscode-server/releases/download/openvscode-server-${OPENVSCODE_VERSION}/openvscode-server-${OPENVSCODE_VERSION}-linux-x64.tar.gz" \
        -o "openvscode-server-${OPENVSCODE_VERSION}-linux-x64.tar.gz" \
 && tar xzf "openvscode-server-${OPENVSCODE_VERSION}-linux-x64.tar.gz" \
 && chown -R ${USER}:${USER} "openvscode-server-${OPENVSCODE_VERSION}-linux-x64" \
 && ln -s "/opt/archives/openvscode-server-${OPENVSCODE_VERSION}-linux-x64" /opt/openvscode-server

USER ${USER}

# Disable Workspace Trust prompts
RUN mkdir -p ${HOME}/.openvscode-server/data/User \
 && printf '{\n  "security.workspace.trust.enabled": false\n}\n' \
      > ${HOME}/.openvscode-server/data/User/settings.json

COPY --chown=${USER}:${USER} . ${HOME}/ygm-tutorial/

# Pre-build the YGM tutorial exercises
WORKDIR ${HOME}/ygm-tutorial
RUN mkdir -p build \
 && cd build \
 && cmake -DBUILD_TESTING=OFF .. \
 && make -j$(nproc)

USER root
ADD ./containers/tutorial/supervisord.conf /etc/supervisord.conf
RUN sed -i "s/XXX/${USER}/g" /etc/supervisord.conf

RUN touch /var/log/openvscode-server.log \
 && chown -R ${USER}:${USER} /var/log/openvscode-server.log

EXPOSE 3000

CMD ["/usr/bin/supervisord"]
