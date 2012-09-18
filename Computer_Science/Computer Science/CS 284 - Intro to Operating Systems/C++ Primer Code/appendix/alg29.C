#include <algorithm>
#include <vector>
#include <iostream.h>
	 
void print_char( char elem ) { cout << elem ; }
void (*ppc)( char ) = print_char;

/* generates:
ilmsu   ilmus   ilsmu   ilsum   ilums   ilusm   imlsu   imlus   
imslu   imsul   imuls   imusl   islmu   islum   ismlu   ismul   
isulm   isuml   iulms   iulsm   iumls   iumsl   iuslm   iusml   
limsu   limus   lismu   lisum   liums   liusm   lmisu   lmius   
lmsiu   lmsui   lmuis   lmusi   lsimu   lsium   lsmiu   lsmui   
lsuim   lsumi   luims   luism   lumis   lumsi   lusim   lusmi   
milsu   milus   mislu   misul   miuls   miusl   mlisu   mlius   
mlsiu   mlsui   mluis   mlusi   msilu   msiul   msliu   mslui   
msuil   msuli   muils   muisl   mulis   mulsi   musil   musli   
silmu   silum   simlu   simul   siulm   siuml   slimu   slium   
slmiu   slmui   sluim   slumi   smilu   smiul   smliu   smlui   
smuil   smuli   suilm   suiml   sulim   sulmi   sumil   sumli   
uilms   uilsm   uimls   uimsl   uislm   uisml   ulims   ulism   
ulmis   ulmsi   ulsim   ulsmi   umils   umisl   umlis   umlsi   
umsil   umsli   usilm   usiml   uslim   uslmi   usmil   usmli 
*/

int main()
{
	vector<char,allocator> vec(5);
		
	// the character sequence: musil
	vec[0] = 'm'; vec[1] = 'u'; vec[2] = 's';
	vec[3] = 'i'; vec[4] = 'l'; 
		
	int cnt = 2;
	sort( vec.begin(), vec.end() );
	for_each( vec.begin(), vec.end(), ppc ); cout << "\t";
		
	// generate all the permutations of ``musil''
	while( next_permutation( vec.begin(), vec.end())) 
        {
                for_each( vec.begin(), vec.end(), ppc ); 
		cout << "\t";
		    
		if ( ! ( cnt++ % 8 )) {
                       cout << "\n";
		       cnt = 1;
		}
	}
		
	cout << "\n\n";
	return 0;
}
