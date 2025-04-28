CC := gcc

CFLAGES := -O2 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wpointer-arith -Wtype-limits -Wempty-body -Wno-logical-op -Wstrict-prototypes -Wold-style-declaration -Wold-style-definition -Wmissing-parameter-type -Wmissing-field-initializers -Wnested-externs -Wno-pointer-sign -Wno-unused-result -std=gnu99 -lm

X_FILE := Markov

help: ## Show help
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-20s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

compile: Markov.c ## Compile programm
	@${CC} -o ${X_FILE} $(CFLAGES) Markov.c

run: compile ## Compile and run programm
	@./${X_FILE}

clean: ## Clean output file
	@rm $(X_FILE) 2>/dev/null || true
