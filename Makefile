build:
	$(MAKE) -C js
	$(MAKE) -C c
	$(MAKE) -C python
	$(MAKE) -C java
	$(MAKE) -C rust
	$(MAKE) -C elixir

run:
	$(MAKE) -C js run
	$(MAKE) -C c run
	$(MAKE) -C python run
	$(MAKE) -C java run
	$(MAKE) -C rust run
	$(MAKE) -C elixir run
