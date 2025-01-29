# イメージ名とコンテナ名を変数として定義
IMAGE_NAME = cpp-ros2-kubota
CONTAINER_NAME = cpp-ros2-container
DOCKERFILE_NAME = Dockerfiles/ros2-dockerfile

# ユーザー情報
USERNAME := $(shell whoami)
UID := $(shell id -u)
GID := $(shell id -g)

# 現在のディレクトリを取得
WORKSPACE = $(shell pwd)

# ビルドターゲット
build:
	docker build \
		--build-arg USERNAME=$(USERNAME) \
		--build-arg USER_UID=$(UID) \
		--build-arg USER_GID=$(GID) \
		--build-arg CONTAINER_NAME=$(CONTAINER_NAME) \
		-f $(DOCKERFILE_NAME) \
		-t $(IMAGE_NAME)-$(USERNAME) Dockerfiles

# 実行ターゲット
run:
	@echo "Container Name: $(CONTAINER_NAME)-$(USERNAME)"
	@echo "Image Name: $(IMAGE_NAME)-$(USERNAME)"
	@echo "User: $(USERNAME) (UID: $(UID), GID: $(GID))"
	docker run --rm -v $(WORKSPACE):/workspace \
		--name $(CONTAINER_NAME)-$(USERNAME) \
		--network host \
		-it $(IMAGE_NAME)-$(USERNAME)

# 既存のコンテナに接続するターゲット
exec:
	docker exec -it $(CONTAINER_NAME)-$(USERNAME) zsh

# ワークスペースのパーミッション修正
fix-permissions:
	sudo chown -R $(UID):$(GID) $(WORKSPACE)

# クリーンアップターゲット
clean:
	docker rmi -f $(IMAGE_NAME)-$(USERNAME)

# ヘルプターゲット
help:
	@echo "Usage:"
	@echo "  make build              Build the Docker image for current user ($(USERNAME))"
	@echo "  make run               Run the Docker container"
	@echo "  make exec              Connect to running container"
	@echo "  make fix-permissions   Fix workspace permissions"
	@echo "  make clean             Remove the Docker image"
	@echo ""
	@echo "Current configuration:"
	@echo "  Username: $(USERNAME)"
	@echo "  UID: $(UID)"
	@echo "  GID: $(GID)"
	@echo "  Workspace: $(WORKSPACE)"

# 同名のファイルが存在しても必ず実行される。buildディレクトリがあっても実行される。
.PHONY: build run exec fix-permissions clean help mkdir-workspace
