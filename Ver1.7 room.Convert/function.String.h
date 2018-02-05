// make strOut = strIn
void makeStr(char *strIn, char *strOut){
	int i = 0;
	while (strIn[i] != '\0'){
		strOut[i] = strIn[i];
		i++;
	}
	strOut[i] = '\0';
}
