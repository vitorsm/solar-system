# solar-system
> TP 02 computação gráfica

## Descrição
Implementação de um sistema estelar em C++ usando OpenGL, FreeGlut e Soil.
A implementacao possui 2 camadas:
1. models: possui os modelos utilizados para o desenvolvimento das regras do sistema
1. controllers: possui os controladores de visulizacao, é responsavel pelas regras de negocio

A classe Main informa as funções de callback da GLUT. Todas as funções de callback estão na classe Controller, que é o controle principal do jogo, todos os outros controles se comunicam com ela. Ela chama todos os controles que precisam desenhar na tela:

```c
void Controller::drawScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (Controller::screenId == Controller::SCREEN_PARAMS_ID) {

	} else if (Controller::screenId == Controller::SCREEN_PLANETS_ID) {
		if (showCamera3) {
			glPushMatrix();
				glTranslated(satelliteCamera[0], satelliteCamera[1], satelliteCamera[2]);
				glutWireCube(1);
			glPopMatrix();
		}

		celestialBodyController->drawCelestialBodies(angle, showRoute, onLight);
	}

	glutSwapBuffers();
}
```

### Controles
O Controller é a classe de controle principal do jogo, ele importa todas as outras classes de controle, ou seja, as demais classes de controle estão no mesmo nível:
* ```CelestialBodyController```: Responsavel por desenhar tudo referente aos corpos celestes.
* ```ParamsController```: Responsavel por pegar os parametros da simulação
* ```Controller```: Responsável pelo controle das teclas e pegar o que o controle dos corpos celestes desenhou

O código do jogo possui comentários para explicação de partes onde existe alguma logica complexa.

## Estrutura de diretorios
```
lunarlander
│   README.md
|   makefile
│___images
│
└───src
    │   Main.cpp
    │   Utils.cpp
    │   Utils.h
    │
    └───models
    |
    └───controllers
    |
    └───resources

```

## makefile
Para executar o sistema estelar basta estar no diretorio raiz e executar o comando make, após o jogo ser compilado basta usar o comando make run

Para iniciar a simulação basta pressionar enter;

## Funcionalidades extras implementadas

* Órbitas não circulares
* Modo de órbitas visíveis
* Navegação completa usando wasd
* Uso do git

