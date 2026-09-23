#include <stdio.h>

float fahrenheit2celsius(float temperature)
{
	float celsiusOut = (temperature - 32) * 5 / 9;
	return celsiusOut;
}

float celsius2fahrenheit(float temperature)
{
	float fahrenheitOut = (temperature * 9/5) + 32;
	return fahrenheitOut;
}

int main(void) 
{	
	float temperature = 0;
	int userChoice = 0;
	
	do 
	{
		printf("Welcome to my C temperature converter! \n");
		printf("Please select the # you'd like to calculate: \n");
		printf("1) Convert from Fahrenheit to Celsius. \n");
		printf("2) Convert from Celsius to Fahrenheit. \n");
		printf("3) Leave the C program. \n");
		scanf("%d", &userChoice);
		
		if (userChoice == 1) 
		{
			float temperature = 0.0;
			printf("Enter a temperature in Fahrenheit: ");
			scanf("%f", &temperature);
			printf("Temperature in Celsius: %.2f \n", fahrenheit2celsius(temperature));
		}
		
		else if (userChoice == 2) 
		{
			float temperature = 0.0;
			printf("Enter a temperature in Celsius: ");
			scanf("%f", &temperature);
			printf("Temperature in Fahrenheit: %.2f \n", celsius2fahrenheit(temperature));
		}
		
		else if (userChoice == 3)
		{
			printf("Ending program. Goodbye. \n");
		}
		
		else
		{
			printf("Bad entry. Try again! \n");
		}
	}
	 
	while (userChoice != 3);
	return 0;
}


