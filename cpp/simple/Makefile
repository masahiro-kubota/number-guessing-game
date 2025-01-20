# イメージ名とコンテナ名を変数として定義
IMAGE_NAME = ros2-kubota
CONTAINER_NAME = ros2-container
# 現在のディレクトリを取得するMakefileの記法
WORKSPACE = $(shell pwd)
# ビルドターゲット
build:
	docker build -t $(IMAGE_NAME) .

# 実行ターゲット
run:
	docker run --rm -v $(WORKSPACE):/workspace -it --name $(CONTAINER_NAME) $(IMAGE_NAME)

# 既存のコンテナに接続するターゲット
exec:
	docker exec -it $(CONTAINER_NAME) zsh

fix-permissions:
	sudo chown -R $(shell id -u):$(shell id -g) $(WORKSPACE)

# クリーンアップターゲット (不要なイメージを削除)
clean:
	docker rmi -f $(IMAGE_NAME)

# ヘルプターゲット
help:
	@echo "Usage:"
	@echo "  make build      Build the Docker image."
	@echo "  make run        Run the Docker container."
	@echo "  make clean      Remove the Docker image."
