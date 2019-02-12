class Color{
	public :
	static void init(){
		for (int i=0;i<16;i++){
			system[i]=i;
		}
		for (int i=0;i<25;i++){
			system[i]=257-25+i;
		}
	}
	static short transparent;
	static short system[16];//0..15
	static short gray[25];
	static short rgb(int red, int green, int blue) {
		if (red>5||green>5||blue>5){
		return 0;
		}
  return 16 + (red * 36) + (green * 6) + blue;
}
	
};