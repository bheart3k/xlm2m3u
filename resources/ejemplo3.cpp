#include <stdio.h>
#include <string.h>

char *trim(char *s)
{
  char *start = s;

  /* Nos comemos los espacios al inicio */
  while(*start && isspace(*start))
    ++start;

  char *i = start;
  char *end = start;

  /* Nos comemos los espacios al final */
  while(*i)
  {
    if( !isspace(*(i++)) )
      end = i;
  }

  /* Escribimos el terminados */
  *end = 0;

  return start;
}

char *trim2(char *s, const char *trimChars)
{
  char *start = s;

  /* Nos comemos los caracteres al principio */
  while(*start && strpbrk((const char*)start, trimChars)==start)
    ++start;

  char *i = start;
  char *end = start;

  /* Nos comemos los caracteres al final */
  while(*i)
  {
    if( strpbrk(i++, trimChars)!=i-1 )
      end = i;
  }

  /* Coloramos el perminador */
  *end = 0;

  return start;
}

int main()
{
  char mi_cadena[30]="\f\n Cadena; \tSucia \n\t ;";
  printf("Mi cadena inicialmente: \"%s\"\n", mi_cadena);
  printf("Mi cadena tras trim(): \"%s\"\n", trim(mi_cadena));
  printf("Mi cadena tras trim2(): \"%s\"\n", trim2(mi_cadena,";\f\n\t"));
}