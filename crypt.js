/* This is for testing only

var to_crypt_str="Test me by uncommenting below";

var key = [75,10,18,255];
var salt = [0,6,2,8];

to_crypt=[];

for(idx=0;idx<to_crypt_str.length;idx++)
{
	to_crypt[idx]=to_crypt_str.charCodeAt(idx);
}
*/

////////////////////////
//-- IMPLEMENTATION --//
////////////////////////

function crypt8(to_crypt,key,salt)
{

	var nb_d=key.length;

	for(i=to_crypt.length%key.length;i!=0;i--)
	{
		to_crypt[to_crypt.length]=0;
	}

	vectorized = [];
	
	for(i=0;i<to_crypt.length;i++)
	{
		vectorized[i]=(to_crypt[i]/10000*(1+key[i%nb_d]))+salt[i%nb_d];
	}
	return vectorized;
}

function add8(cypher1,position,value,key,salt){

	var nb_d=key.length;

	s_c=(value)/10000*(1+key[position%nb_d]);
	
	cypher1[position]+=s_c;
	
	return cypher1;
}

function multiply8(cypher1,position,value,key,salt){

	var nb_d=key.length;

	s_c=value*(cypher1[position]-salt[position%nb_d])+salt[position%nb_d];
	
	cypher1[position]=s_c;
	
	return cypher1;
}

function decrypt8(cypher,key,salt)
{
	var nb_d=key.length;

	unvectorized=[];
	
	for(i=0;i<cypher.length;i++)
	{
		unvectorized[i]=(Math.round((cypher[i]-salt[i%nb_d])/(1+key[i%nb_d])*10000));
	}
	return unvectorized;
}

///////////////
//-- TESTS --//
///////////////
//console;
//console.log;
//print = console.log;
/*
print(to_crypt);
cyp = crypt8(to_crypt,key,salt);
print(cyp);
decyp = decrypt8(cyp,key,salt);
print(decyp);
*/