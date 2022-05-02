#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
using namespace std;

const int LUNGHEZZA_MAX = 50 ;
const int VOTI_MAX = 30;

struct Materia
{
	char nome[LUNGHEZZA_MAX];
	float voti[VOTI_MAX];
	float media;
	Materia* succ;
};

typedef Materia* lista;

void InserisciOrdinatamente(lista&, Materia);
bool EstraiOrdinatamente(lista&,Materia&);
void StampaLista_ScrivisuFile(lista,const char*,int,Materia);
void OrdinaVoti(Materia, int);
bool confronta(char*, char*);

int n;

int main()
{
	bool sentinella = true;
	char input , name[LUNGHEZZA_MAX];
	lista materie = 0;
	Materia materia;
	materia.succ = 0;
	float totale = 0;
	bool quante_volte_in_S = false;
	
	
	do{
		cout << "MENU'" << endl;
		cout << "a) Per aggiungere una materia" << endl;
		cout << "b) Per eliminare materia e voti" << endl;
		cout << "s) Per visualizzare e salvare le materie su file" << endl;
		cout << "c) Per uscire" << endl;
		cin >> input;
		
		switch(input){
			           case 'a':
			                 cout << "Inserisci il nome della materia(senza spazi): ";
			                 cin >> materia.nome;
			                 cout << "Inserisci il numero di voti di " << materia.nome << " : " ;
			                 cin >> n;
			                 
			                 for(int i=0 ; i<n ; i++)
			                    {
                                    cout << "Inserisci il voto di " << materia.nome << " : " ; 
									cin >> materia.voti[i];
									totale += materia.voti[i];
								} 
								
						     materia.media = totale/n;
						     totale = 0;
						     
						     InserisciOrdinatamente(materie,materia);
                             quante_volte_in_S = false;
						     break;
				      
				       case 'b':
				             cout << "Inserisci la materia da eliminare: " ;
				             cin >> materia.nome;
				             if(EstraiOrdinatamente(materie,materia))
				                 cout << endl <<"Hai eliminato " <<  materia.nome << " , " << " media: " << fixed << setprecision(2) << materia.media;
				                else
				                   cout << endl << "Materia non presente nella lista !" << endl;     

                            quante_volte_in_S = false;             
			                 break;
			           
			           case 'c':
                             if(!quante_volte_in_S)
                               {
                                   cout << "Attenzione non puoi uscire senza prima aver salvato. DIGITA: s" << endl;
                                   break;
                               }
			                 sentinella = false;
			                 cout << "Inserisci il tuo nome: " ;
			                 cin >> name;     
			                 break;
			           
			           case 's':
                             quante_volte_in_S = true;
			                 StampaLista_ScrivisuFile(materie,"medie.txt",n,materia);
			                 break;
			                 
			           default:
			                 cout << endl << "Usa solo i caratteri consentiti ! " << endl;
			                 break; 
		             }
	
	   cout << endl << endl ;
		
	  }while(sentinella);
	  
	cout << "CIAO " << name << " A PRESTO ! " << endl;

  return 0;
}


void InserisciOrdinatamente(lista& inizio , Materia daIns) // ok
{
	lista p,q,r;
	
	for(q=inizio ; q!=0 && q->media > daIns.media ; q=q->succ)
	            p = q;
	
	r = new Materia;
	*r = daIns;
	r->succ = q;
	
    if(inizio == q)  inizio = r;
      else p->succ = r;
}

bool EstraiOrdinatamente(lista& inizio , Materia& estratto)   // ok
{
	lista p,q;
	for(q = inizio ; q != 0 && !confronta(q->nome,estratto.nome) ; q = q->succ)
	       p = q ; 
	
	if(q==0)  
	    return false;
	
	estratto = *q;
	estratto.succ = 0;
	
	if(q == inizio) inizio = q->succ;
	  else p->succ = q->succ ;
	
	delete q;
	return true;
}


void StampaLista_ScrivisuFile(lista materie, const char* nomeFile, int num_voti, Materia materia)
{
	if(materie == 0){
		               cout << "La lista e' vuota! " << endl;
		               return;
	                }
	
	/*
	    Serve per creare un file di testo al interno del quale ci saranno le materie con la media,
	    ed infine la media totale 
	*/
	
	float totale;
	int contatore = 0;
	fstream file;
	file.open(nomeFile , ios::app);
	cout << endl ;
	while(materie != 0)
	     {
			 cout << materie->nome << " " << fixed << setprecision(2) << materie->media << endl;
			 totale += materie->media;
			 
            	// Restituisce la data odierna : 
                time_t now = time(0); 
                char* dt = ctime(&now);  
                file << "Data e ora del salvataggio: " << dt << endl;

			 file << materie->nome;
			  for(int i=0 ; i<num_voti ; i++) 
			    {
					OrdinaVoti(materia,num_voti);
					file << " " << materie->voti[i] << " ";
			    } 
		     file << " " << "Media: " << fixed << setprecision(2) << materie->media << endl;
		     file << endl;
			 
			 materie = materie->succ;
			 contatore++;
			 
	     }
       

    cout << "Media scolastica totale: " << fixed << setprecision(2) << totale/contatore << endl;
    file << "Media scolastica totale: " << fixed << setprecision(2) << totale/contatore << endl;
    file << endl << endl << "**********************************" << endl << endl ;
    file.close();
}

void OrdinaVoti(Materia materia , int num_voti)   // BUBBLE SORT , ok 
{
  bool scambiati = true;
  int temp;
  
  while(scambiati) 
       {
		   scambiati = false;
		   
		   for(int i=0 ; i<num_voti-1 ; i++)
		      {
				  if(materia.voti[i] < materia.voti[i+1])  
				     {
						 temp = materia.voti[i];
						 materia.voti[i] = materia.voti[i+1];
						 materia.voti[i+1] = temp;
						 scambiati = true;
				     }
			  }
	   }
}

bool confronta(char* str1 , char* str2) // ok
{
	while(*str1 == *str2)
	     {
			 if(*str1 == '\0') 
			    return true;
 			 
			 str1++ ;
			 str2++ ;
		 }
   return false;
}