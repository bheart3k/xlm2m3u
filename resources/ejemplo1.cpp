#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <ctype.h>

/* Lo podemos sacar de http://totaki.com/poesiabinaria/2010/03/trim-un-gran-amigo-php-c-c/ */
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

void print_nodes(xmlNode *first_child, int level)
{
  xmlNode *node;
  int l;
  xmlChar *value;
  xmlAttr *prop;

  for (node = first_child; node; node = node->next) {

    /* Si el nodo hijo es de texto y no tiene contenido... */
    if ( (node->type==3) && (strlen(trim((char*)xmlNodeGetContent(node)))==0) )
      continue;

    /* Escribimos tabs para dirigirnos al nivel deseado */
    for (l=0; l<level; l++)
      printf("\t");
    
    /* Averiguamos el valor del nodo */
    value=xmlNodeGetContent(node);
    printf("Child <%s> (t:%d) => \"%s\" ", node->name, node->type, trim((char*)value));

    /* Si tengo propiedades (atributos del nodo) las proceso */
    if (node->properties!=NULL)
      {
    printf (" props (");
    prop=node->properties;
    while (prop!=NULL)  /* Mientras haya una propiedad, la */
      {         /* voy a mostrar */
        value=xmlGetProp(node, prop->name);
        /* Si el valor no es NULL lo pongo en pantalla */
        if (value!=NULL)
          printf ("[%s]=\"%s\" ", prop->name, xmlGetProp(node, prop->name));
        /* Me dirijo a la siguiente propiedad */
        prop=prop->next;
      }
    printf(")");
      }
    printf ("\n");
    /* Si el nodo tiene sub-nodos, los proceso recursivamente */
    if (node->children!=NULL)
      print_nodes(node->children, level+1);
  }

}

int main(int argc, char **argv) {
   xmlDoc *document;
   xmlNode *root, *first_child;
   char *filename;

   if (argc < 2) {
     fprintf(stderr, "Usage: %s filename.xml\n", argv[0]);
     return 1;
   }
   filename = argv[1];

  document = xmlReadFile(filename, NULL, 0);
  root = xmlDocGetRootElement(document);
  fprintf(stdout, "Root is <%s> (%i)\n", root->name, root->type);
  first_child = root->children;
  print_nodes(first_child, 1);
  fprintf(stdout, "Fin\n");
  return 0;
}