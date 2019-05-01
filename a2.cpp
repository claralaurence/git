#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


struct protein
{
   string gi;
   string Ref;
   string name;
   string protein_sequence;
};

int main()
{string iname;
 ifstream ist;
 int the_one;
 bool menu_two = false;
 ofstream file;
 file.open("selected_proteins.txt");
  	

	cout<<"Welcome to Protein Database \n"<<endl;
	cout<<"Select an option from the menu below"<<endl;

	cout<<"1) Load the abridged protein data"<<endl;
	cout<<"2) Load the complete protein data"<<endl;
	cout<<"3) Quit database"<<endl;


	int database_choice_1;
	cout<<">>";
	cin>> database_choice_1;
	if (database_choice_1 == 1)
	{
        cout<<"Loading database..."<<endl;
        ist.open("protein_a.fa");
    }

	else if (database_choice_1 == 2)
	{
        cout<<"Loading database..."<<endl;
        ist.open("protein_c.fa");
	}
	if (database_choice_1 == 3)
	{
		file.close();
	    return 0;
	}
	
	
	//Once the protein is opened, we want to organise its content
	
	
	vector<protein> v;      //declaration of vector called v that contains protein (structure declared outside the main)
	protein test;
	string temp_s;               //Temporary string that will store value (to then name it) while it reads the file 
	int temp_int;
	getline(ist,temp_s,'>');      //getline until the terminator > then removes it 
	while(!ist.eof())                  //While it doesn't reach end of the file
	{
		getline(ist,temp_s,'|');   //getline until the terminator | then removes it (the one after the gi)
		getline(ist,temp_s,'|');       //get what's in between the two || ie : gi
		test.gi = temp_s;
		getline(ist,temp_s,'|');     // getline until a new | but doesn't store it anywhere (ie ref|)
		getline(ist,temp_s,'|');        
		test.Ref = temp_s;
	    getline(ist,temp_s,'\n');      
		test.name = temp_s;
		getline(ist,temp_s,'>');
		test.protein_sequence = temp_s;
		
		v.push_back(test);       //push_back : Adds a new element at the end of the vector, after its current last element.
	}
	cout<<"Database loaded."<<endl;
int database_choice_2 = 0;
while (	database_choice_2 != 6)
{
	menu_two = false;
cout<<"Select an option from the menu below"<<endl;
cout<<"1) Overview of the database "<<endl;
cout<<"2) Search by protein #"<<endl;
cout<<"3) Search by gi #"<<endl;
cout<<"4) Search by ref #"<<endl;
cout<<"5) Search by keyword"<<endl;
cout<<"6) Quit database"<<endl;
cout<<">>";


cin>> database_choice_2;

if (database_choice_2 == 1)

{   cout<<"The proteins in the database are from GenBank(R)"<<endl;
    cout<<"Total number of proteins in the database: "<<v.size()<<endl;
    cout<<"Amino acids are represented by the following characters:"<<endl;
    cout<<"A  alanine               P  proline \nB  aspartate/asparagine  Q  glutamine \nC  cystine               R  arginine \nD  aspartate             S  serine \nE  glutamate             T  threonine \nF  phenylalanine         U  selenocysteine \nG  glycine               V  valine \nH  histidine             W  tryptophan \nI  isoleucine            Y  tyrosine \nK  lysine                Z  glutamate/glutamine \nL  leucine               X  any \nM  methionine            *  translation stop \nN  asparagine            -  gap of indeterminate length"<<endl;
	menu_two = false;
}

if (database_choice_2 == 2)
{
	int t;
	cout<<"Enter an item id: "<<endl;
	cin>> t;
	if (t>0 && t<=v.size()+1)
	{
	the_one=t-1;
	menu_two = true;
	}	
}

if (database_choice_2 == 3)
{
	cout<<"Enter a gi: "<<endl;
	string gi_to_find;
	cin>> gi_to_find;
	for(int t = 0; t < v.size(); t++)
	{
		if (v[t].gi == gi_to_find)
		{
			the_one=t;
			menu_two = true;
		}
	}
}

if (database_choice_2 == 4)
{
	cout<<"Enter a ref: "<<endl;
	string ref_to_find;
	cin>> ref_to_find;
	for(int t = 0; t < v.size(); t++)
	{
		if (v[t].Ref == ref_to_find)
		{
			the_one=t;
			menu_two = true;
		}
	}
}
if (database_choice_2 == 5)
{
	cout<<"Enter a keyword\n"<<endl;
	cout<<">>";
	string keyword;
	cin>>keyword;
	vector <protein> find;
	int found_keyword=0;
	int number_of_results=1;
	int match;
	vector<int> value_of_t;
	for(int t = 0; t < v.size(); t++)
	{
		if(v[t].name.find(keyword) != string::npos)	
		{
			value_of_t.push_back(t);
			find.push_back(v[t]);
			found_keyword++;
		}
	}
	if(found_keyword !=0)
	{
		cout<<"Number of matches found: "<<found_keyword<<endl;
		for(int a=0;a<found_keyword;a++)
		{
			cout<<number_of_results<<")  item id: "<<value_of_t[a]+1<<", gi id:"<<find[a].gi<<", ref id"<<find[a].Ref<<endl;
	        cout<<find[a].name<<endl;
			number_of_results++;
		}
	}
	cout<<"Select one of the matches\n"<<">>";
	cin>>match;
	if (match > 0 && match <=found_keyword)
	{
		the_one = (value_of_t[match-1]);
		menu_two = true;
	}
	
}



int database_choice_3 = 0;

if (menu_two)
{
while (database_choice_3 != 5)
{
	cout<<"Select an option from the menu below"<<endl;
cout<<"1) Description of the protein"<<endl;
cout<<"2) Protein sequence"<<endl;
cout<<"3) Protein statistics"<<endl;
cout<<"4) Record protein to file "<<endl;
cout<<"5) Return to the main menu "<<endl;
cout<<">>";
	cin>> database_choice_3;
if (database_choice_3 == 1)
{
	cout<<"Description of the protein"<<endl;
	cout<<"item id: "<<the_one+1<<endl;
	cout<<"gi id: "<< v[the_one].gi<<endl;
	cout<<"ref id:  "<<v[the_one].Ref<<endl;
	cout<<"name: "<<v[the_one].name<<"]"<<endl;	
}

if(database_choice_3 ==2)
{   
    cout<<"Protein sequence: \n"<<v[the_one].protein_sequence<<endl;	
}

if(database_choice_3 ==3)
{   
    cout<<"Report on the protein statistics: "<<endl;
	
	string protein_sequence_string = v[the_one].protein_sequence;
	int x = v[the_one].protein_sequence.length();
	cout<<"Total number of amino acids: "<<x<<endl;
	int A=0,B=0,C=0,D=0,E=0,F=0,G=0,H=0,I=0,J=0,K=0,L=0,M=0,N=0,P=0,Q=0,R=0,S=0,T=0,U=0,V=0,W=0,Y=0,Z=0,X=0,times=0,dash=0;
	for(int n = 0; n < x; n++)
	{
		if (protein_sequence_string[n] == 'A')
		{
			A++;
		}
		if (protein_sequence_string[n] == 'B')
		{
			B++;
		}
		if (protein_sequence_string[n] == 'C')
		{
			C++;
		}
		if (protein_sequence_string[n] == 'D')
		{
			D++;
		}
		if (protein_sequence_string[n] == 'E')
		{
			E++;
		}
		if (protein_sequence_string[n] == 'F')
		{
			F++;
		}
		if (protein_sequence_string[n] == 'G')
		{
			G++;
		}
		if (protein_sequence_string[n] == 'H')
		{
			H++;
		}
		if (protein_sequence_string[n] == 'I')
		{
			I++;
		}
		if (protein_sequence_string[n] == 'K')
		{
			K++;
		}
		if (protein_sequence_string[n] == 'L')
		{
			L++;
		}
		if (protein_sequence_string[n] == 'M')
		{
			M++;
		}
		if (protein_sequence_string[n] == 'N')
		{
			N++;
		}
		if (protein_sequence_string[n] == 'P')
		{
			P++;
		}
		if (protein_sequence_string[n] == 'Q')
		{
			Q++;
		}
		if (protein_sequence_string[n] == 'R')
		{
			R++;
		}
		if (protein_sequence_string[n] == 'S')
		{
			S++;
		}
		if (protein_sequence_string[n] == 'T')
		{
			T++;
		}
		if (protein_sequence_string[n] == 'U')
		{
			U++;
		}
		if (protein_sequence_string[n] == 'V')
		{
			V++;
		}
		if (protein_sequence_string[n] == 'W')
		{
			W++;
		}
		if (protein_sequence_string[n] == 'Y')
		{
			Y++;
		}
		if (protein_sequence_string[n] == 'Z')
		{
			Z++;
		}
		if (protein_sequence_string[n] == 'X')
		{
			X++;
		}
		if (protein_sequence_string[n] == '*')
		{
			times++;
		}
		if (protein_sequence_string[n] == '-')
		{
			dash++;
		}
	}
cout<<"A  "<<A<<"\tP  "<<P<<endl;
cout<<"B  "<<B<<"\tQ  "<<Q<<endl;
cout<<"C  "<<C<<"\tR  "<<R<<endl;
cout<<"D  "<<D<<"\tS  "<<S<<endl;
cout<<"E  "<<E<<"\tT  "<<T<<endl;
cout<<"F  "<<F<<"\tU  "<<U<<endl;
cout<<"G  "<<G<<"\tV  "<<V<<endl;
cout<<"H  "<<H<<"\tW  "<<W<<endl;
cout<<"I  "<<I<<"\tY  "<<Y<<endl;
cout<<"K  "<<K<<"\tZ  "<<Z<<endl;
cout<<"L  "<<L<<"\tX  "<<X<<endl;
cout<<"M  "<<M<<"\t*  "<<times<<endl;
cout<<"N  "<<N<<"\t-  "<<dash<<endl;
}
if(database_choice_3 ==4)
{
   
	
	file<<v[the_one].gi<<endl;
	file<<v[the_one].Ref<<endl;
	file<<v[the_one].name<<"]"<<endl;
	file<<v[the_one].protein_sequence<<endl;
	
	
	cout<<"The protein was written to file."<<endl;
}
}
}
}
file.close();
return 0;
}
