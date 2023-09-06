#include "FPToolkit.c"
#include <stdbool.h>

char u[1000000];
char s[10];
char w[10][1000];
char temp[100000000];

void l_sys(int depth, int rules){
  if(depth == 0){
    return;
  }
  bool match = false;
  char nomatch[2];
  temp[0] = '\0';
  int stringsize = strlen(u);

  for(int i = 0; i < stringsize; i++){
    for(int j = 0; j < rules; j++){
      if(u[i] == s[j]){
        strcat(temp, w[j]);
        match = true;
        break;
      }else{
        match = false;
      }
    }
    if(match == false){
      // if there was no rule for the character
      nomatch[0] = u[i];
      nomatch[1] = '\0';
      strcat(temp, nomatch);
    }
  }
  strcpy(u, temp);
  l_sys(depth-1, rules);
}

int main(){
  double units_moved = 4.67;
  double degrees = 60;
  double radians = (M_PI/180)*degrees;
  double turtle[2], potential[2];
  int numrules, depth;

  u[0] = 'A';
  numrules = 2;
  s[0] = 'A';
  s[1] = 'B';
  depth = 7;

  for(int i = 0; i < numrules; i++){
    printf("\nReplace '%c' with: ", s[i]);
    scanf("%s", &w[i][0]);
  }
  
  l_sys(depth, numrules);

  double string_size = strlen(u);

  double width = 600;
  double height = 600;
  G_init_graphics(width, height);
  G_rgb(0.0, 0.0, 0.0);
  G_clear();

  double temp[2];
  turtle[0] = 0;
  turtle[1] = 0;
  potential[0] = turtle[0] + units_moved;
  potential[1] = 0;
  double n = 37;
  double n_copy = 1;
  double gap = height/n;
  double width_copy = 0;
  double gap_copy = gap;

  while(n_copy <= n){
    G_rgb(0.0, width/600.0, (width/255.0));
    G_line(width, height, 0, width);
    G_rgb((width/255.0), (width)/600.0, 0.0);
    width = width - gap;
    G_line(height,width_copy, width,height);
    width_copy = width_copy + gap;
    n_copy += 1;
  }
  
  for(int i = 0; i < string_size; i++){
    if((int)u[i] == 43){
      potential[0] = potential[0] - turtle[0];
      potential[1] = potential[1] - turtle[1];
      temp[0] = potential[0]*cos(radians) + potential[1]*sin(radians);
      temp[1] = (-potential[0])*sin(radians) + potential[1]*cos(radians);
      potential[0] = temp[0] + turtle[0];
      potential[1] = temp[1] + turtle[1];
    }
    
    if((int)u[i] == 45){
      potential[0] = potential[0] - turtle[0];
      potential[1] = potential[1] - turtle[1];
      temp[0] = potential[0]*cos(radians) - potential[1]*sin(radians);
      temp[1] = potential[0]*sin(radians) + potential[1]*cos(radians);
      potential[0] = temp[0] + turtle[0];
      potential[1] = temp[1] + turtle[1];
    }
    
    if((int)u[i] >= 65 && (int)u[i] <= 90){
      G_rgb(turtle[0]/potential[1], turtle[1]*0.47/potential[1], turtle[1]/potential[0]);
      G_line(turtle[0], turtle[1], potential[0], potential[1]);
      temp[0] = potential[0] - turtle[0];
      temp[1] = potential[1] - turtle[1];
      turtle[0] = potential[0];
      turtle[1] = potential[1];
      potential[0] += temp[0];
      potential[1] += temp[1];
    }
  }
  
  printf("Path finished!\n");

  G_wait_key();
  G_save_to_bmp_file("lsys.bmp");
}