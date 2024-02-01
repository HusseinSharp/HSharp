// Copyright (c) 2023 HusseinSharp(H#)
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdbool.h>

// Add these global flags
bool includeKeyPressHandling = false;
bool includeMouseHandling = false;
SDL_Window *window = NULL;
%}

%union {
   int num;
   char *str;
}

%token <str> EQUALS
%token <str> SEMICOLON
%token <str> PLUS
%token <str> MINUS
%token <str> MULTIPLY
%token <str> DIVIDE
%token  LPAR
%token COLOR
%token RGB
%token  RPAR
%token <str> LCB
%token <str> RCB
%token  MAIN
%token <str> CALL
%token VAR
%token <num> NUMBER
%token <str> IDENT
%token <str> LSB
%token <str> RSB
%token <str> COMMA
%token <str> ON_MOUSE
%token <str> ON_KEYPRESS

%token <str> SYS 
%token CREATEWINDOW


%type <num> expr
%type <num> clvl
%type <str> var_declaration assignment display
%type <str> statement_list



%left PLUS MINUS
%left MULTIPLY DIVIDE

%%

mainprog: MAIN LCB statement_list RCB SEMICOLON;

statement_list: /* empty */
              | statement_list statement SEMICOLON
              ;

statement: var_declaration | assignment | display|wincrt|wincrtevent;

var_declaration:  IDENT LSB RSB { insert_array($1); }
               | VAR IDENT { insert_variable($2); };

assignment: IDENT EQUALS expr { update_variable($1, $3); }
          | IDENT LSB expr RSB EQUALS expr { update_array_element($1, $3, $6); };

display: CALL IDENT { display_variable($2); }
       | CALL IDENT LSB expr RSB { display_array_element($2, $4); };
       
       clvl: NUMBER{
    if($1<= 255 || $1 >= 0){
        $$ = $1;
    }
    else{
        fprintf(stderr, "Error: invalid value, value set to 0");
        $$ = 0 ;
    };
    
    };



expr: NUMBER { $$ = $1; }
   | IDENT { $$ = get_variable_value($1); }
   | IDENT LSB expr RSB { $$ = get_array_element_value($1, $3); }
   | expr PLUS expr { $$ = $1 + $3; }
   | expr MINUS expr { $$ = $1 - $3; }
   | expr MULTIPLY expr { $$ = $1 * $3; }
   | expr DIVIDE expr {
       if ($3 != 0) {
           $$ = $1 / $3;
       } else {
           fprintf(stderr, "Error: Division by zero\n");
           $$ = 0; // You can handle division by zero differently if needed
       }
   }
   | '(' expr ')' { $$ = $2; }
   ;





wincrt: SYS CREATEWINDOW LPAR IDENT COMMA expr COMMA expr RPAR {
    // SDL window creation code
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow($4, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, $6, $8, 0);
    if (!window) {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    // Event loop
  

    SDL_Event event;
    int quit = 0;

    while (!quit) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDL_KEYDOWN:
                        // Handle key press if includeKeyPressHandling is true
                       
                        if (includeKeyPressHandling) {
                            printf("Key pressed: %c\n", event.key.keysym.sym);
                        }
                        break;
                    case SDL_KEYUP:
                        // Handle key release if includeKeyPressHandling is true
                     
                        if (includeKeyPressHandling) {
                            printf("Key released: %c\n", event.key.keysym.sym);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        // Handle mouse button press if includeMouseHandling is true
                       
                        if (includeMouseHandling) {
                            printf("Mouse button %d pressed at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                     
                        // Handle mouse button release if includeMouseHandling is true
                        if (includeMouseHandling) {
                            printf("Mouse button %d released at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                        }
                        break;
                    case SDL_MOUSEMOTION:
                    
                        // Handle mouse motion if includeMouseHandling is true
                        if (includeMouseHandling) {
                            printf("Mouse moved to (%d, %d)\n", event.motion.x, event.motion.y);
                        }
                        break;
                }
            }
    }

        // Add your rendering code or other logic here
        // SDL_RenderClear(renderer);
        // ... (your rendering code)
        // SDL_RenderPresent(renderer);
    

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
| SYS CREATEWINDOW LPAR IDENT COMMA expr COMMA expr COMMA COLOR RGB LPAR clvl COMMA clvl COMMA clvl RPAR RPAR {
    // SDL window creation code
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow($4, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, $6, $8, 0);
    if (!window) {
        fprintf(stderr, "Error creating SDL window: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, $13, $15, $17, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    // Event loop


    SDL_Event event;
    int quit = 0;
   while (!quit) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDL_KEYDOWN:
                        // Handle key press if includeKeyPressHandling is true
                        
                        if (includeKeyPressHandling) {
                            printf("Key pressed: %c\n", event.key.keysym.sym);
                        }
                        break;
                    case SDL_KEYUP:
                        // Handle key release if includeKeyPressHandling is true
                       
                        if (includeKeyPressHandling) {
                            printf("Key released: %c\n", event.key.keysym.sym);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
          
                        // Handle mouse button press if includeMouseHandling is true
                        if (includeMouseHandling) {
                            printf("Mouse button %d pressed at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                    
                        // Handle mouse button release if includeMouseHandling is true
                        if (includeMouseHandling) {
                            printf("Mouse button %d released at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                        }
                        break;
                    case SDL_MOUSEMOTION:
                   
                        // Handle mouse motion if includeMouseHandling is true
                        if (includeMouseHandling) {
                            printf("Mouse moved to (%d, %d)\n", event.motion.x, event.motion.y);
                        }
                        break;
                }
            }
   }
    
    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

;

   

wincrtevent: SYS ON_KEYPRESS {
    if (&window) {
     
        includeKeyPressHandling = true;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Handle quit event
                    break;
                case SDL_KEYDOWN:
                    // Handle key press if includeKeyPressHandling is true
                    if (includeKeyPressHandling) {
                        printf("Key pressed: %c\n", event.key.keysym.sym);
                    }
                    break;
                case SDL_KEYUP:
                    // Handle key release if includeKeyPressHandling is true
                    if (includeKeyPressHandling) {
                        printf("Key released: %c\n", event.key.keysym.sym);
                    }
                    break;
            }
        }
    } else {
        printf("No window\n");
        includeKeyPressHandling = false;
    }
}
| SYS ON_MOUSE {
    if (&window) {
      
         includeMouseHandling = true;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Handle quit event
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Handle mouse button press if includeMouseHandling is true
                    if (includeMouseHandling) {
                        printf("Mouse button %d pressed at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    // Handle mouse button release if includeMouseHandling is true
                    if (includeMouseHandling) {
                        printf("Mouse button %d released at (%d, %d)\n", event.button.button, event.button.x, event.button.y);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    // Handle mouse motion if includeMouseHandling is true
                    if (includeMouseHandling) {
                        printf("Mouse moved to (%d, %d)\n", event.motion.x, event.motion.y);
                    }
                    break;
            }
        }
    } else {
        printf("No window\n");
         includeMouseHandling = false;
    }
};



%%
void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
