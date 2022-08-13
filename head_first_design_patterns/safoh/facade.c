/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facade.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saladuit <safoh@student.codam.nl>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 22:09:53 by saladuit          #+#    #+#             */
/*   Updated: 2022/06/23 22:30:51 by saladuit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	dog_love()
{
printf("       __		\n");
printf("    __/o \\_		\n");
printf("    \\____  \\		\n");
printf("        /   \\		\n");
printf("  __   //\\   \\		\n");
printf("_/o \\-//--\\   \\_/		\n");
printf("____  ___  \\  |		\n");
printf("    ||   \\ |\\ |		\n");
printf("   _||   _||_||		\n");
}
void dog_one()
{

printf("           __\n");
printf("\\,--------'()'--o\n");
printf("(_    ___    /~\"\n");
printf(" (_)_)  (_)_)\n");
}
void dog_two()
{
printf("  __\n");
printf("-''|\\_____/)\n");
printf("\\_/|_)     )\n");
printf("   \\  __  /\n");
printf("   (_/ (_/  \n");
}
void	find_dogs()
{
	dog_one();
	dog_two();
}

int main(void)
{
	find_dogs();
	dog_love();
}
