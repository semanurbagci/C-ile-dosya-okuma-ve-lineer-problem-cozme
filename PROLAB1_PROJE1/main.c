#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <math.h>


struct ilkbessatir{

    char format[150];
    char versiyon[150];
    char alanlar[150];
    char noktalar[150];
    char data[150];

};

struct noktalar{

    float x,y,z;
    int r,g,b;

};

struct rgbsiz_binary{
    float x,y,z;
};

int main()
{
    DIR *file=opendir("C:\\Users\\asus\\Desktop\\PROLAB1\\PROJE1\\PROLAB1_PROJE1");

    struct dirent *icindekidosyalar;
    char kontrol[100];
    char *search;
    char tut[50][50];
    int p,u=0;

    FILE *output=fopen("output.nkt","w");
    if(output==NULL){
        printf("Dosya acilamadi.");
    }
    fclose(output);



    struct ilkbessatir satir;
    char nktlr[15], alnlr[15], vrsyn[15];
    int k;
    int v;
    char points[100];
    int satirkontrolsayac=0;
    int satir_kontrol_rgb[100];
    int sayac=0;
    int t=0;
    int nokta_say_rgbli;
    int nokta_say_rgbsiz;
    int hata=0;

    int secim;
    int i,j;

    int birincinoktauzak;
    int ikincinoktauzak;
    int birincinoktayakin;
    int ikincinoktayakin;
    float enuzaksonuc=0;
    float enyakinsonuc=1000;

    float enkucukx=1000;
    float enbuyukx=0;
    float enkucuky=1000;
    float enbuyuky=0;
    float enkucukz=1000;
    float enbuyukz=0;
    float kenar=-1;

    int case4_sayac=0;
    float kure_merkez_x;
    float kure_merkez_y;
    float kure_merkez_z;
    float kure_yaricap;
    int kure_nokta_sayisi=0;

    float uzaklik;
    float toplam_uzaklik=0.0;
    int uzaklik_sayisi=0;
    float ort_uzaklik;

    if(file==NULL){
        printf("Klasor acilamadi\n");
    }

    if(file!=NULL){
       printf("--- .nkt UZANTILI BUTUN DOSYALAR: ---\n");

        while((icindekidosyalar=readdir(file))!=NULL){

            strcpy(kontrol,icindekidosyalar->d_name);
            search=strstr(kontrol,".nkt");

            if(search!=NULL){
                strcpy(tut[u],kontrol);
                printf("%s\n", tut[u]);
                u++;
            }
        }

        for(p=0;p<u;p++){

            FILE *dosya=fopen(tut[p],"r");

          printf("ISLEM YAPILMAKTA OLAN DOSYA: %s\n",tut[p]);

          fgets(satir.format,150,dosya);
          fgets(satir.versiyon,150,dosya);

          sscanf(satir.versiyon,"%s %d",vrsyn,&v);

          fgets(satir.alanlar,150,dosya);
          fgets(satir.noktalar,150,dosya);
          fgets(satir.data,150,dosya);


          char *ara_ptr_a=strstr(satir.data,"ascii");
          char *ara_ptr_b=strstr(satir.data,"binary");

          char *araptr=strstr(satir.alanlar,"r g b");
          char *araptr1=strstr(satir.alanlar,"x y z");
          char *araptr2=strstr(satir.alanlar,"rgb");
          char *araptr3=strstr(satir.alanlar,"rg b");
          char *araptr4=strstr(satir.alanlar,"r gb");



            if(ara_ptr_b!=NULL){
                if(araptr==NULL && araptr1!=NULL && araptr2==NULL && araptr3==NULL && araptr4==NULL){
                   sscanf(satir.noktalar,"%s %d",nktlr, &k);
                   struct rgbsiz_binary rsiz_bin[k];
                   for(i=0;i<k;i++){
                    fread(&rsiz_bin,sizeof(rsiz_bin),1,dosya);
                    t++;
                   }
                   nokta_say_rgbsiz=t;
                   t=0;


                   if(araptr1==NULL){
                     hata++;
                   }
                   while(1){
                    printf("\n--- MENU ---\n");
                    printf("1-Dosya kontrolu\n");
                    printf("2-En uzak/en yakin noktalar\n");
                    printf("3-Kup\n");
                    printf("4-Kure\n");
                    printf("5-Nokta uzakliklarinin ortalamasi\n");
                    printf("6-Cikis\n");
                    printf("\n\nSeciminizi yapiniz:");

                    scanf("%d", &secim);

                    if(secim==6){
                      break;
                    }

                    switch(secim){
                    case 1:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\nSecim 1: \n");

                        if(v!=1){

                            printf("Versiyon bilgisi hatalidir,islem yapilamaz.\nBir sonraki dosyaya gecmek icin 6'ya basiniz.");
                            fprintf(output,"Versiyon bilgisi hatalidir,islem yapilamaz.\n");

                            break;
                        }

                        if(hata!=0){
                            printf("Dosya ALANLAR x y z formatina uygun degildir.\nDiger islemler yapilamaz. Bir sonraki dosyaya gecmek icin 6'ya basiniz.\n");
                            fprintf(output,"Dosya ALANLAR x y z formatina uygun degildir.\n");
                            hata=0;
                            break;
                        }

                        if(nokta_say_rgbsiz==k){
                            printf("Nokta sayilari esittir.\n");
                            fprintf(output,"Nokta sayilari esittir.\n");

                        }
                        else if(nokta_say_rgbsiz!=k){
                            printf("Nokta sayilari esit degildir.\n");
                            fprintf(output,"Nokta sayilari esit degildir.\n");
                        }

                        fclose(output);

                        break;

                    case 2:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        for(i=0;i<k;i++){
                          for(j=i+1;j<k;j++){
                             if ((sqrt(((rsiz_bin[i].x)-(rsiz_bin[j].x))*((rsiz_bin[i].x)-(rsiz_bin[j].x)))+(((rsiz_bin[i].y)-(rsiz_bin[j].y))*((rsiz_bin[i].y)-(rsiz_bin[j].y)))+(((rsiz_bin[i].z)-(rsiz_bin[j].z))*((rsiz_bin[i].z)-(rsiz_bin[j].z))))>enuzaksonuc)
                             {
                               birincinoktauzak=i;
                               ikincinoktauzak=j;
                               enuzaksonuc= (sqrt(((rsiz_bin[i].x)-(rsiz_bin[j].x))*((rsiz_bin[i].x)-(rsiz_bin[j].x)))+(((rsiz_bin[i].y)-(rsiz_bin[j].y))*((rsiz_bin[i].y)-(rsiz_bin[j].y)))+(((rsiz_bin[i].z)-(rsiz_bin[j].z))*((rsiz_bin[i].z)-(rsiz_bin[j].z))));
                             }
                          }
                        }

                        for(i=0;i<k;i++){
                           for(j=i+1;j<k;j++){
                             if ((sqrt(((rsiz_bin[i].x)-(rsiz_bin[j].x))*((rsiz_bin[i].x)-(rsiz_bin[j].x)))+(((rsiz_bin[i].y)-(rsiz_bin[j].y))*((rsiz_bin[i].y)-(rsiz_bin[j].y)))+(((rsiz_bin[i].z)-(rsiz_bin[j].z))*((rsiz_bin[i].z)-(rsiz_bin[j].z))))<enyakinsonuc)
                             {
                               birincinoktayakin=i;
                               ikincinoktayakin=j;
                               enyakinsonuc= (sqrt(((rsiz_bin[i].x)-(rsiz_bin[j].x))*((rsiz_bin[i].x)-(rsiz_bin[j].x)))+(((rsiz_bin[i].y)-(rsiz_bin[j].y))*((rsiz_bin[i].y)-(rsiz_bin[j].y)))+(((rsiz_bin[i].z)-(rsiz_bin[j].z))*((rsiz_bin[i].z)-(rsiz_bin[j].z))));
                             }
                          }
                        }


                        fprintf(output,"\n2. Secim: \n");

                        printf("\nBirbirine en uzak nokta numaralari :%d ve %d : \n", birincinoktauzak,ikincinoktauzak);
                        printf("\nBirinci noktanin x koordinati: %f", rsiz_bin[birincinoktauzak].x);
                        printf("\nBirinci noktanin y koordinati: %f", rsiz_bin[birincinoktauzak].y);
                        printf("\nBirinci noktanin z koordinati: %f", rsiz_bin[birincinoktauzak].z);
                        fprintf(output,"Birbirine en uzak nokta numaralari :%d ve %d : \n", birincinoktauzak,ikincinoktauzak);
                        fprintf(output,"Birinci noktanin x koordinati: %f\n", rsiz_bin[birincinoktauzak].x);
                        fprintf(output,"Birinci noktanin y koordinati: %f\n", rsiz_bin[birincinoktauzak].y);
                        fprintf(output,"Birinci noktanin z koordinati: %f\n", rsiz_bin[birincinoktauzak].z);


                        printf("\nIkinci noktanin x koordinati: %f",  rsiz_bin[ikincinoktauzak].x);
                        printf("\nIkinci noktanin y koordinati: %f",  rsiz_bin[ikincinoktauzak].y);
                        printf("\nIkinci noktanin z koordinati: %f",  rsiz_bin[ikincinoktauzak].z);
                        fprintf(output,"Ikinci noktanin x koordinati: %f\n",  rsiz_bin[ikincinoktauzak].x);
                        fprintf(output,"Ikinci noktanin y koordinati: %f\n",  rsiz_bin[ikincinoktauzak].y);
                        fprintf(output,"Ikinci noktanin z koordinati: %f\n",  rsiz_bin[ikincinoktauzak].z);


                        printf("\nBirbirine en yakin nokta numaralari :%d ve %d : \n", birincinoktayakin,ikincinoktayakin);
                        printf("\nBirinci noktanin x koordinati: %f", rsiz_bin[birincinoktayakin].x);
                        printf("\nBirinci noktanin y koordinati: %f", rsiz_bin[birincinoktayakin].y);
                        printf("\nBirinci noktanin z koordinati: %f", rsiz_bin[birincinoktayakin].z);
                        fprintf(output,"Birbirine en yakin nokta numaralari :%d ve %d : \n", birincinoktayakin,ikincinoktayakin);
                        fprintf(output,"Birinci noktanin x koordinati: %f\n", rsiz_bin[birincinoktayakin].x);
                        fprintf(output,"Birinci noktanin y koordinati: %f\n", rsiz_bin[birincinoktayakin].y);
                        fprintf(output,"Birinci noktanin z koordinati: %f\n", rsiz_bin[birincinoktayakin].z);



                        printf("\nIkinci noktanin x koordinati: %f",  rsiz_bin[ikincinoktayakin].x);
                        printf("\nIkinci noktanin y koordinati: %f",  rsiz_bin[ikincinoktayakin].y);
                        printf("\nIkinci noktanin z koordinati: %f\n",  rsiz_bin[ikincinoktayakin].z);
                        fprintf(output,"Ikinci noktanin x koordinati: %f\n",  rsiz_bin[ikincinoktayakin].x);
                        fprintf(output,"Ikinci noktanin y koordinati: %f\n",  rsiz_bin[ikincinoktayakin].y);
                        fprintf(output,"Ikinci noktanin z koordinati: %f\n",  rsiz_bin[ikincinoktayakin].z);

                        fclose(output);

                        break;

                    case 3:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }


                        for(i=0;i<k;i++){

                            if(rsiz_bin[i].x<enkucukx){
                                enkucukx=rsiz_bin[i].x;
                            }
                            if(rsiz_bin[i].y<enkucuky){
                                enkucuky=rsiz_bin[i].y;
                            }
                            if(rsiz_bin[i].z<enkucukz){
                                enkucukz=rsiz_bin[i].z;
                            }
                            if(rsiz_bin[i].x>enbuyukx){
                                enbuyukx=rsiz_bin[i].x;
                            }
                            if(rsiz_bin[i].y>enbuyuky){
                                enbuyuky=rsiz_bin[i].y;
                            }
                            if(rsiz_bin[i].z>enbuyukz){
                                enbuyukz=rsiz_bin[i].z;
                            }
                        }

                        fprintf(output,"\n3. Secim: \n");

                        float xler=enbuyukx-enkucukx;
                        float yler=enbuyuky-enkucuky;
                        float zler=enbuyukz-enkucukz;


                        if(xler>=yler && xler>=zler){
                            kenar=xler;
                        }
                         if(yler>=xler && yler>=zler){
                            kenar=yler;
                        }
                         if(zler>=yler && zler>=xler){
                            kenar=zler;
                        }

                        float kose1x=enkucukx;
                        float kose1y=enkucuky;
                        float kose1z=enkucukz;

                        float kose2x=kose1x;
                        float kose2y=kose1y+kenar;
                        float kose2z=kose1z;

                        float kose3x=kose1x;
                        float kose3y=kose1y;
                        float kose3z=kose1z+kenar;

                        float kose4x=kose1x+kenar;
                        float kose4y=kose1y;
                        float kose4z=kose1z;

                        float kose5x=kose1x+kenar;
                        float kose5y=kose1y;
                        float kose5z=kose1z+kenar;

                        float kose6x=kose1x;
                        float kose6y=kose1y+kenar;
                        float kose6z=kose1z+kenar;

                        float kose7x=kose1x+kenar;
                        float kose7y=kose1y+kenar;
                        float kose7z=kose1z+kenar;

                        float kose8x=kose1x+kenar;
                        float kose8y=kose1y+kenar;
                        float kose8z=kose1z;


                        printf("\n\nButun noktalari icine alan en kucuk kupun 1. kose noktalari: %f %f %f\n",kose1x, kose1y, kose1z);
                        printf("Butun noktalari icine alan en kucuk kupun 2. kose noktalari: %f %f %f\n",kose2x, kose2y, kose2z);
                        printf("Butun noktalari icine alan en kucuk kupun 3. kose noktalari: %f %f %f\n",kose3x, kose3y, kose3z);
                        printf("Butun noktalari icine alan en kucuk kupun 4. kose noktalari: %f %f %f\n",kose4x, kose4y, kose4z);
                        printf("Butun noktalari icine alan en kucuk kupun 5. kose noktalari: %f %f %f\n",kose5x, kose5y, kose5z);
                        printf("Butun noktalari icine alan en kucuk kupun 6. kose noktalari: %f %f %f\n",kose6x, kose6y, kose6z);
                        printf("Butun noktalari icine alan en kucuk kupun 7. kose noktalari: %f %f %f\n",kose7x, kose7y, kose7z);
                        printf("Butun noktalari icine alan en kucuk kupun 8. kose noktalari: %f %f %f\n",kose8x, kose8y, kose8z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 1. kose noktalari: %f %f %f\n",kose1x, kose1y, kose1z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 2. kose noktalari: %f %f %f\n",kose2x, kose2y, kose2z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 3. kose noktalari: %f %f %f\n",kose3x, kose3y, kose3z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 4. kose noktalari: %f %f %f\n",kose4x, kose4y, kose4z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 5. kose noktalari: %f %f %f\n",kose5x, kose5y, kose5z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 6. kose noktalari: %f %f %f\n",kose6x, kose6y, kose6z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 7. kose noktalari: %f %f %f\n",kose7x, kose7y, kose7z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 8. kose noktalari: %f %f %f\n",kose8x, kose8y, kose8z);

                        fclose(output);

                        break;

                    case 4:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\n4. Secim: \n");


                        if(case4_sayac==0){
                           printf("\nYaricap ve xyz noktalarini bosluklu bir sekilde giriniz:");
                           scanf("%f %f %f %f",&kure_yaricap,&kure_merkez_x,&kure_merkez_y,&kure_merkez_z);
                           case4_sayac++;
                        }


                        for(i=0;i<k;i++)
                        {
                            if (kure_yaricap>=(sqrt(((rsiz_bin[i].x)-kure_merkez_x)*((rsiz_bin[i].x)-kure_merkez_x))+(((rsiz_bin[i].y)-kure_merkez_y)*((rsiz_bin[i].y)-kure_merkez_y))+(((rsiz_bin[i].z)-kure_merkez_z)*((rsiz_bin[i].z)-kure_merkez_z))))
                            {

                              kure_nokta_sayisi++;
                              printf("%d. indeksteki nokta, koordinatlari:%f %f %f\n",i,rsiz_bin[i].x,rsiz_bin[i].y,rsiz_bin[i].z);
                              fprintf(output,"%d. indeksteki nokta, koordinatlari:%f %f %f\n",i,rsiz_bin[i].x,rsiz_bin[i].y,rsiz_bin[i].z);
                            }
                        }

                        printf("Kure icinde ya da uzerinde kalan nokta sayisi:%d", kure_nokta_sayisi);
                        fprintf(output,"Kure icinde ya da uzerinde kalan nokta sayisi:%d\n", kure_nokta_sayisi);
                        kure_nokta_sayisi=0;

                        fclose(output);

                        break;

                    case 5:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\n5. Secim: \n");

                        for(i=0;i<k;i++){
                            for(j=i+1;j<k;j++){
                                uzaklik=(sqrt(((rsiz_bin[i].x)-(rsiz_bin[j].x))*((rsiz_bin[i].x)-(rsiz_bin[j].x)))+(((rsiz_bin[i].y)-(rsiz_bin[j].y))*((rsiz_bin[i].y)-(rsiz_bin[j].y)))+(((rsiz_bin[i].z)-(rsiz_bin[j].z))*((rsiz_bin[i].z)-(rsiz_bin[j].z))));
                                toplam_uzaklik+=uzaklik;
                                uzaklik_sayisi++;
                            }
                        }
                        ort_uzaklik=toplam_uzaklik/uzaklik_sayisi;
                        printf("\nOrtalama uzaklik=%f\n",ort_uzaklik);
                        fprintf(output,"Ortalama uzaklik=%f\n",ort_uzaklik);

                        fclose(output);

                        break;
                    }

                   }
                }

                if(araptr!=NULL && araptr1!=NULL){

                    hata=0;

                    sscanf(satir.noktalar,"%s %d",nktlr, &k);
                    struct noktalar rli_bin[k];

                    for(i=0;i<k;i++){
                    fread(&rli_bin,sizeof(rli_bin),1,dosya);
                    t++;
                   }
                   nokta_say_rgbli=t;
                   t=0;


                   if(araptr1==NULL || araptr2!=NULL || araptr3!=NULL || araptr4!=NULL){
                     hata++;
                   }

                   while(1){
                    printf("\n--- MENU ---\n");
                    printf("1-Dosya kontrolu\n");
                    printf("2-En uzak/en yakin noktalar\n");
                    printf("3-Kup\n");
                    printf("4-Kure\n");
                    printf("5-Nokta uzakliklarinin ortalamasi\n");
                    printf("6-Cikis\n");
                    printf("\n\nSeciminizi yapiniz:");

                    scanf("%d", &secim);

                    if(secim==6){
                        break;
                    }

                    switch(secim){
                    case 1:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\n1. Secim: \n");

                        if(v!=1){
                            printf("Versiyon bilgisi hatalidir,islem yapilamaz.\nBir sonraki dosyaya gecmek icin 6'ya basiniz.");
                            fprintf(output,"Versiyon bilgisi hatalidir,islem yapilamaz.\n");

                            break;
                        }

                        if(hata!=0){


                            printf("Dosya ALANLAR x y z r g b formatina uygun degildir.\nDiger islemler yapilamaz. Bir sonraki dosyaya gecmek icin 6'ya basiniz.\n");
                            fprintf(output,"Dosya ALANLAR x y z r g b formatina uygun degildir. Diger islemler yapilamaz.\n");
                            hata=0;
                            break;
                        }

                        if(nokta_say_rgbsiz==k){
                            printf("Nokta sayilari esittir.\n");
                            fprintf(output,"Nokta sayilari esittir.\n");
                        }
                        else if(nokta_say_rgbsiz!=k){
                            printf("Nokta sayilari esit degildir.\n");
                            fprintf(output,"Nokta sayilari esit degildir.\n");
                        }

                        fclose(output);
                        break;

                    case 2:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\n2. Secim: \n");


                        for(i=0;i<k;i++){
                          for(j=i+1;j<k;j++){
                             if ((sqrt(((rli_bin[i].x)-(rli_bin[j].x))*((rli_bin[i].x)-(rli_bin[j].x)))+(((rli_bin[i].y)-(rli_bin[j].y))*((rli_bin[i].y)-(rli_bin[j].y)))+(((rli_bin[i].z)-(rli_bin[j].z))*((rli_bin[i].z)-(rli_bin[j].z))))>enuzaksonuc)
                             {
                               birincinoktauzak=i;
                               ikincinoktauzak=j;
                               enuzaksonuc= (sqrt(((rli_bin[i].x)-(rli_bin[j].x))*((rli_bin[i].x)-(rli_bin[j].x)))+(((rli_bin[i].y)-(rli_bin[j].y))*((rli_bin[i].y)-(rli_bin[j].y)))+(((rli_bin[i].z)-(rli_bin[j].z))*((rli_bin[i].z)-(rli_bin[j].z))));
                             }
                          }
                        }

                        for(i=0;i<k;i++){
                           for(j=i+1;j<k;j++){
                             if ((sqrt(((rli_bin[i].x)-(rli_bin[j].x))*((rli_bin[i].x)-(rli_bin[j].x)))+(((rli_bin[i].y)-(rli_bin[j].y))*((rli_bin[i].y)-(rli_bin[j].y)))+(((rli_bin[i].z)-(rli_bin[j].z))*((rli_bin[i].z)-(rli_bin[j].z))))<enyakinsonuc)
                             {
                               birincinoktayakin=i;
                               ikincinoktayakin=j;
                               enyakinsonuc= (sqrt(((rli_bin[i].x)-(rli_bin[j].x))*((rli_bin[i].x)-(rli_bin[j].x)))+(((rli_bin[i].y)-(rli_bin[j].y))*((rli_bin[i].y)-(rli_bin[j].y)))+(((rli_bin[i].z)-(rli_bin[j].z))*((rli_bin[i].z)-(rli_bin[j].z))));
                             }
                          }
                        }


                        printf("\nBirbirine en uzak nokta numaralari :%d ve %d : \n", birincinoktauzak,ikincinoktauzak);
                        printf("\nBirinci noktanin x koordinati: %f", rli_bin[birincinoktauzak].x);
                        printf("\nBirinci noktanin y koordinati: %f", rli_bin[birincinoktauzak].y);
                        printf("\nBirinci noktanin z koordinati: %f", rli_bin[birincinoktauzak].z);
                        fprintf(output,"Birbirine en uzak nokta numaralari :%d ve %d : \n", birincinoktauzak,ikincinoktauzak);
                        fprintf(output,"Birinci noktanin x koordinati: %f\n", rli_bin[birincinoktauzak].x);
                        fprintf(output,"Birinci noktanin y koordinati: %f\n", rli_bin[birincinoktauzak].y);
                        fprintf(output,"Birinci noktanin z koordinati: %f\n", rli_bin[birincinoktauzak].z);

                        printf("\nIkinci noktanin x koordinati: %f",  rli_bin[ikincinoktauzak].x);
                        printf("\nIkinci noktanin y koordinati: %f",  rli_bin[ikincinoktauzak].y);
                        printf("\nIkinci noktanin z koordinati: %f", rli_bin[ikincinoktauzak].z);
                        fprintf(output,"Ikinci noktanin x koordinati: %f\n",  rli_bin[ikincinoktauzak].x);
                        fprintf(output,"Ikinci noktanin y koordinati: %f\n",  rli_bin[ikincinoktauzak].y);
                        fprintf(output,"Ikinci noktanin z koordinati: %f\n", rli_bin[ikincinoktauzak].z);

                        printf("\nBirbirine en yakin nokta numaralari :%d ve %d : \n", birincinoktayakin,ikincinoktayakin);
                        printf("\nBirinci noktanin x koordinati: %f", rli_bin[birincinoktayakin].x);
                        printf("\nBirinci noktanin y koordinati: %f", rli_bin[birincinoktayakin].y);
                        printf("\nBirinci noktanin z koordinati: %f", rli_bin[birincinoktayakin].z);
                        fprintf(output,"Birbirine en yakin nokta numaralari :%d ve %d : \n", birincinoktayakin,ikincinoktayakin);
                        fprintf(output,"Birinci noktanin x koordinati: %f\n", rli_bin[birincinoktayakin].x);
                        fprintf(output,"Birinci noktanin y koordinati: %f\n", rli_bin[birincinoktayakin].y);
                        fprintf(output,"Birinci noktanin z koordinati: %f\n", rli_bin[birincinoktayakin].z);

                        printf("\nIkinci noktanin x koordinati: %f",  rli_bin[ikincinoktayakin].x);
                        printf("\nIkinci noktanin y koordinati: %f",  rli_bin[ikincinoktayakin].y);
                        printf("\nIkinci noktanin z koordinati: %f\n",  rli_bin[ikincinoktayakin].z);
                        fprintf(output,"Ikinci noktanin x koordinati: %f\n",  rli_bin[ikincinoktayakin].x);
                        fprintf(output,"Ikinci noktanin y koordinati: %f\n",  rli_bin[ikincinoktayakin].y);
                        fprintf(output,"Ikinci noktanin z koordinati: %f\n",  rli_bin[ikincinoktayakin].z);

                        fclose(output);

                        break;

                    case 3:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\n3. Secim: \n");


                        for(i=0;i<k;i++){

                            if(rli_bin[i].x<enkucukx){
                                enkucukx=rli_bin[i].x;
                            }
                            if(rli_bin[i].y<enkucuky){
                                enkucuky=rli_bin[i].y;
                            }
                            if(rli_bin[i].z<enkucukz){
                                enkucukz=rli_bin[i].z;
                            }
                            if(rli_bin[i].x>enbuyukx){
                                enbuyukx=rli_bin[i].x;
                            }
                            if(rli_bin[i].y>enbuyuky){
                                enbuyuky=rli_bin[i].y;
                            }
                            if(rli_bin[i].z>enbuyukz){
                                enbuyukz=rli_bin[i].z;
                            }
                        }

                        float xler=enbuyukx-enkucukx;
                        float yler=enbuyuky-enkucuky;
                        float zler=enbuyukz-enkucukz;


                        if(xler>=yler && xler>=zler){
                            kenar=xler;
                        }
                         if(yler>=xler && yler>=zler){
                            kenar=yler;
                        }
                         if(zler>=yler && zler>=xler){
                            kenar=zler;
                        }

                        float kose1x=enkucukx;
                        float kose1y=enkucuky;
                        float kose1z=enkucukz;

                        float kose2x=kose1x;
                        float kose2y=kose1y+kenar;
                        float kose2z=kose1z;

                        float kose3x=kose1x;
                        float kose3y=kose1y;
                        float kose3z=kose1z+kenar;

                        float kose4x=kose1x+kenar;
                        float kose4y=kose1y;
                        float kose4z=kose1z;

                        float kose5x=kose1x+kenar;
                        float kose5y=kose1y;
                        float kose5z=kose1z+kenar;

                        float kose6x=kose1x;
                        float kose6y=kose1y+kenar;
                        float kose6z=kose1z+kenar;

                        float kose7x=kose1x+kenar;
                        float kose7y=kose1y+kenar;
                        float kose7z=kose1z+kenar;

                        float kose8x=kose1x+kenar;
                        float kose8y=kose1y+kenar;
                        float kose8z=kose1z;


                        printf("\n\nButun noktalari icine alan en kucuk kupun 1. kose noktalari: %f %f %f\n",kose1x, kose1y, kose1z);
                        printf("Butun noktalari icine alan en kucuk kupun 2. kose noktalari: %f %f %f\n",kose2x, kose2y, kose2z);
                        printf("Butun noktalari icine alan en kucuk kupun 3. kose noktalari: %f %f %f\n",kose3x, kose3y, kose3z);
                        printf("Butun noktalari icine alan en kucuk kupun 4. kose noktalari: %f %f %f\n",kose4x, kose4y, kose4z);
                        printf("Butun noktalari icine alan en kucuk kupun 5. kose noktalari: %f %f %f\n",kose5x, kose5y, kose5z);
                        printf("Butun noktalari icine alan en kucuk kupun 6. kose noktalari: %f %f %f\n",kose6x, kose6y, kose6z);
                        printf("Butun noktalari icine alan en kucuk kupun 7. kose noktalari: %f %f %f\n",kose7x, kose7y, kose7z);
                        printf("Butun noktalari icine alan en kucuk kupun 8. kose noktalari: %f %f %f\n",kose8x, kose8y, kose8z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 1. kose noktalari: %f %f %f\n",kose1x, kose1y, kose1z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 2. kose noktalari: %f %f %f\n",kose2x, kose2y, kose2z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 3. kose noktalari: %f %f %f\n",kose3x, kose3y, kose3z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 4. kose noktalari: %f %f %f\n",kose4x, kose4y, kose4z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 5. kose noktalari: %f %f %f\n",kose5x, kose5y, kose5z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 6. kose noktalari: %f %f %f\n",kose6x, kose6y, kose6z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 7. kose noktalari: %f %f %f\n",kose7x, kose7y, kose7z);
                        fprintf(output,"Butun noktalari icine alan en kucuk kupun 8. kose noktalari: %f %f %f\n",kose8x, kose8y, kose8z);

                        fclose(output);

                        break;

                    case 4:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\n4. Secim: \n");


                        if(case4_sayac==0){
                           printf("\nYaricap ve xyz noktalarini bosluklu bir sekilde giriniz:");
                           scanf("%f %f %f %f",&kure_yaricap,&kure_merkez_x,&kure_merkez_y,&kure_merkez_z);
                           case4_sayac++;
                        }

                        for(i=0;i<k;i++)
                        {
                            if(kure_yaricap>=(sqrt(((rli_bin[i].x)-kure_merkez_x)*((rli_bin[i].x)-kure_merkez_x))+(((rli_bin[i].y)-kure_merkez_y)*((rli_bin[i].y)-kure_merkez_y))+(((rli_bin[i].z)-kure_merkez_z)*((rli_bin[i].z)-kure_merkez_z))))
                            {
                              kure_nokta_sayisi++;
                              printf("%d. indeksteki nokta, koordinatlari:%f %f %f\n",i,rli_bin[i].x,rli_bin[i].y,rli_bin[i].z);
                              fprintf(output,"%d. indeksteki nokta, koordinatlari:%f %f %f\n",i,rli_bin[i].x,rli_bin[i].y,rli_bin[i].z);
                            }
                        }

                        printf("Kure icinde ya da uzerinde kalan nokta sayisi:%d",kure_nokta_sayisi);
                        fprintf(output,"Kure icinde ya da uzerinde kalan nokta sayisi:%d\n",kure_nokta_sayisi);
                        kure_nokta_sayisi=0;

                        fclose(output);

                        break;

                    case 5:

                        output=fopen("output.nkt","a");
                        if(output==NULL){
                            printf("Dosya acilamadi.");
                        }

                        fprintf(output,"\n5. Secim: \n");

                        for(i=0;i<k;i++){
                            for(j=i+1;j<k;j++){
                                uzaklik=(sqrt(((rli_bin[i].x)-(rli_bin[j].x))*((rli_bin[i].x)-(rli_bin[j].x)))+(((rli_bin[i].y)-(rli_bin[j].y))*((rli_bin[i].y)-(rli_bin[j].y)))+(((rli_bin[i].z)-(rli_bin[j].z))*((rli_bin[i].z)-(rli_bin[j].z))));
                                toplam_uzaklik+=uzaklik;
                                uzaklik_sayisi++;
                            }
                        }
                        ort_uzaklik=toplam_uzaklik/uzaklik_sayisi;
                        printf("\nOrtalama uzaklik=%f\n",ort_uzaklik);
                        fprintf(output,"Ortalama uzaklik=%f\n",ort_uzaklik);

                        fclose(output);

                        break;

                    }

                   }

                }



        }




        if(ara_ptr_a!=NULL){



                sscanf(satir.noktalar,"%s %d",nktlr, &k);
                struct noktalar b[k];


                sayac=0;

                if(araptr!=NULL && araptr1!=NULL){

                 while(!feof(dosya)){

                     fgets(points,100,dosya);
                     sscanf(points,"%f %f %f %d %d %d" ,&b[sayac].x, &b[sayac].y, &b[sayac].z, &b[sayac].r, &b[sayac].g, &b[sayac].b);

                     if(b[sayac].r==0 && b[sayac].g==0 && b[sayac].b==0){
                        satir_kontrol_rgb[satirkontrolsayac]=sayac;
                        satirkontrolsayac++;
                     }

                     sayac++;
                 }

                hata=0;
                nokta_say_rgbli=sayac;

            }

            if(araptr==NULL && araptr1!=NULL && araptr2==NULL && araptr3==NULL && araptr4==NULL) {

                sayac=0;


            satirkontrolsayac=0;
            while(!feof(dosya)){

                     fgets(points,100,dosya);
                     sscanf(points,"%f %f %f" ,&b[sayac].x, &b[sayac].y, &b[sayac].z);
                     sayac++;
                 }
            }


            nokta_say_rgbsiz=sayac;

            hata=0;

            if(araptr1==NULL || araptr2!=NULL || araptr3!=NULL || araptr4!=NULL){
                hata++;

            }

          while(1){
        printf("\n--- MENU ---\n");
        printf("1-Dosya kontrolu\n");
        printf("2-En uzak/en yakin noktalar\n");
        printf("3-Kup\n");
        printf("4-Kure\n");
        printf("5-Nokta uzakliklarinin ortalamasi\n");
        printf("6-Cikis\n");
        printf("\n\nSeciminizi yapiniz:");

        scanf("%d", &secim);

        if(secim==6){
             break;
          }

          switch(secim){

           case 1:

               output=fopen("output.nkt","a");
                    if(output==NULL){
                        printf("Dosya acilamadi.");
                    }

            fprintf(output,"\n1. Secim: \n");

            if(v!=1){

                        printf("Versiyon bilgisi hatalidir,islem yapilamaz.\nBir sonraki dosyaya gecmek icin 6'ya basiniz.");
                        fprintf(output,"Versiyon bilgisi hatalidir,islem yapilamaz.\n");

                            break;
            }

            if(hata!=0){


                printf("Dosya ALANLAR x y z r g b formatina uygun degildir.\nDiger islemler yapilamaz. Bir sonraki dosyaya gecmek icin 6'ya basiniz.\n");
                fprintf(output,"Dosya ALANLAR x y z r g b formatina uygun degildir. Diger islemler yapilamaz.\n");
                hata=0;
                break;
            }

             if(nokta_say_rgbli==k || nokta_say_rgbsiz==k){
                printf("Nokta sayilari esittir.\n");
                fprintf(output,"Nokta sayilari esittir.\n");
                nokta_say_rgbli=0;
                nokta_say_rgbsiz=0;

                if(satirkontrolsayac>0){
                for(i=0;i<satirkontrolsayac;i++){
                    printf("%d. satirda r g b bilgisi eksiktir.\n", satir_kontrol_rgb[i]);
                    fprintf(output,"%d. satirda r g b bilgisi eksiktir.\n", satir_kontrol_rgb[i]);
                }
                break;
            }

                break;
            }

             if(nokta_say_rgbli!=k || nokta_say_rgbsiz!=k){
                printf("Nokta sayilari esit degildir, islem yapilamaz.\n");
                fprintf(output,"Nokta sayilari esit degildir, islem yapilamaz.\n");
                nokta_say_rgbli=0;
                nokta_say_rgbsiz=0;
                break;
            }

            fclose(output);

                break;


           case 2:

            output=fopen("output.nkt","a");
                if(output==NULL){
                    printf("Dosya acilamadi.");
                }

              fprintf(output,"\n2. Secim: \n");

             for(i=0;i<k;i++){
                for(j=i+1;j<k;j++){
                    if ((sqrt(((b[i].x)-(b[j].x))*((b[i].x)-(b[j].x)))+(((b[i].y)-(b[j].y))*((b[i].y)-(b[j].y)))+(((b[i].z)-(b[j].z))*((b[i].z)-(b[j].z))))>enuzaksonuc)
                        {
                        birincinoktauzak=i;
                        ikincinoktauzak=j;
                        enuzaksonuc= (sqrt(((b[i].x)-(b[j].x))*((b[i].x)-(b[j].x)))+(((b[i].y)-(b[j].y))*((b[i].y)-(b[j].y)))+(((b[i].z)-(b[j].z))*((b[i].z)-(b[j].z))));
                        }
                }
            }

                        for(i=0;i<k;i++){
                           for(j=i+1;j<k;j++){
                         if ((sqrt(((b[i].x)-(b[j].x))*((b[i].x)-(b[j].x)))+(((b[i].y)-(b[j].y))*((b[i].y)-(b[j].y)))+(((b[i].z)-(b[j].z))*((b[i].z)-(b[j].z))))<enyakinsonuc)
                           {
                        birincinoktayakin=i;
                        ikincinoktayakin=j;
                        enyakinsonuc= (sqrt(((b[i].x)-(b[j].x))*((b[i].x)-(b[j].x)))+(((b[i].y)-(b[j].y))*((b[i].y)-(b[j].y)))+(((b[i].z)-(b[j].z))*((b[i].z)-(b[j].z))));
                        }
                }
            }

            printf("\nBirbirine en uzak nokta numaralari :%d ve %d : \n", birincinoktauzak,ikincinoktauzak);
            printf("\nBirinci noktanin x koordinati: %f", b[birincinoktauzak].x);
            printf("\nBirinci noktanin y koordinati: %f", b[birincinoktauzak].y);
            printf("\nBirinci noktanin z koordinati: %f", b[birincinoktauzak].z);
            printf("\nIkinci noktanin x koordinati: %f",  b[ikincinoktauzak].x);
            printf("\nIkinci noktanin y koordinati: %f",  b[ikincinoktauzak].y);
            printf("\nIkinci noktanin z koordinati: %f",  b[ikincinoktauzak].z);
            fprintf(output,"Birbirine en uzak nokta numaralari :%d ve %d : \n", birincinoktauzak,ikincinoktauzak);
            fprintf(output,"Birinci noktanin x koordinati: %f\n", b[birincinoktauzak].x);
            fprintf(output,"Birinci noktanin y koordinati: %f\n", b[birincinoktauzak].y);
            fprintf(output,"Birinci noktanin z koordinati: %f\n", b[birincinoktauzak].z);
            fprintf(output,"Ikinci noktanin x koordinati: %f\n",  b[ikincinoktauzak].x);
            fprintf(output,"Ikinci noktanin y koordinati: %f\n",  b[ikincinoktauzak].y);
            fprintf(output,"Ikinci noktanin z koordinati: %f\n",  b[ikincinoktauzak].z);

            printf("\nBirbirine en yakin nokta numaralari :%d ve %d : \n", birincinoktayakin,ikincinoktayakin);
            printf("\nBirinci noktanin x koordinati: %f", b[birincinoktayakin].x);
            printf("\nBirinci noktanin y koordinati: %f", b[birincinoktayakin].y);
            printf("\nBirinci noktanin z koordinati: %f", b[birincinoktayakin].z);
            printf("\nIkinci noktanin x koordinati: %f",  b[ikincinoktayakin].x);
            printf("\nIkinci noktanin y koordinati: %f",  b[ikincinoktayakin].y);
            printf("\nIkinci noktanin z koordinati: %f\n",  b[ikincinoktayakin].z);
            fprintf(output,"Birbirine en yakin nokta numaralari :%d ve %d : \n", birincinoktayakin,ikincinoktayakin);
            fprintf(output,"Birinci noktanin x koordinati: %f\n", b[birincinoktayakin].x);
            fprintf(output,"Birinci noktanin y koordinati: %f\n", b[birincinoktayakin].y);
            fprintf(output,"Birinci noktanin z koordinati: %f\n", b[birincinoktayakin].z);
            fprintf(output,"Ikinci noktanin x koordinati: %f\n",  b[ikincinoktayakin].x);
            fprintf(output,"Ikinci noktanin y koordinati: %f\n",  b[ikincinoktayakin].y);
            fprintf(output,"Ikinci noktanin z koordinati: %f\n",  b[ikincinoktayakin].z);

            fclose(output);

              break;

           case 3:

              output=fopen("output.nkt","a");
                if(output==NULL){
                    printf("Dosya acilamadi.");
                }

               fprintf(output,"\n3. Secim: \n");


                for(i=0;i<k;i++){

                if(b[i].x<enkucukx){
                    enkucukx=b[i].x;
                }
                if(b[i].y<enkucuky){
                    enkucuky=b[i].y;
                }
                if(b[i].z<enkucukz){
                    enkucukz=b[i].z;
                }

                 if(b[i].x>enbuyukx){
                    enbuyukx=b[i].x;
                }
                if(b[i].y>enbuyuky){
                    enbuyuky=b[i].y;
                }
                if(b[i].z>enbuyukz){
                    enbuyukz=b[i].z;
                }

        }



        float kenar;

        float xler=enbuyukx-enkucukx;
        float yler=enbuyuky-enkucuky;
        float zler=enbuyukz-enkucukz;


        if(xler>yler && xler>zler){
            kenar=xler;
        }
        if(yler>xler && yler>zler){
            kenar=yler;
        }
        if(zler>yler && zler>xler){
            kenar=zler;
        }



        float kose1x=enkucukx;
        float kose1y=enkucuky;
        float kose1z=enkucukz;

        float kose2x=kose1x;
        float kose2y=kose1y+kenar;
        float kose2z=kose1z;

        float kose3x=kose1x;
        float kose3y=kose1y;
        float kose3z=kose1z+kenar;

        float kose4x=kose1x+kenar;
        float kose4y=kose1y;
        float kose4z=kose1z;

        float kose5x=kose1x+kenar;
        float kose5y=kose1y;
        float kose5z=kose1z+kenar;

        float kose6x=kose1x;
        float kose6y=kose1y+kenar;
        float kose6z=kose1z+kenar;

        float kose7x=kose1x+kenar;
        float kose7y=kose1y+kenar;
        float kose7z=kose1z+kenar;

        float kose8x=kose1x+kenar;
        float kose8y=kose1y+kenar;
        float kose8z=kose1z;


        printf("\n\nButun noktalari icine alan en kucuk kupun 1. kose noktalari: %f %f %f\n",kose1x, kose1y, kose1z);
        printf("Butun noktalari icine alan en kucuk kupun 2. kose noktalari: %f %f %f\n",kose2x, kose2y, kose2z);
        printf("Butun noktalari icine alan en kucuk kupun 3. kose noktalari: %f %f %f\n",kose3x, kose3y, kose3z);
        printf("Butun noktalari icine alan en kucuk kupun 4. kose noktalari: %f %f %f\n",kose4x, kose4y, kose4z);
        printf("Butun noktalari icine alan en kucuk kupun 5. kose noktalari: %f %f %f\n",kose5x, kose5y, kose5z);
        printf("Butun noktalari icine alan en kucuk kupun 6. kose noktalari: %f %f %f\n",kose6x, kose6y, kose6z);
        printf("Butun noktalari icine alan en kucuk kupun 7. kose noktalari: %f %f %f\n",kose7x, kose7y, kose7z);
        printf("Butun noktalari icine alan en kucuk kupun 8. kose noktalari: %f %f %f\n",kose8x, kose8y, kose8z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 1. kose noktalari: %f %f %f\n",kose1x, kose1y, kose1z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 2. kose noktalari: %f %f %f\n",kose2x, kose2y, kose2z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 3. kose noktalari: %f %f %f\n",kose3x, kose3y, kose3z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 4. kose noktalari: %f %f %f\n",kose4x, kose4y, kose4z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 5. kose noktalari: %f %f %f\n",kose5x, kose5y, kose5z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 6. kose noktalari: %f %f %f\n",kose6x, kose6y, kose6z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 7. kose noktalari: %f %f %f\n",kose7x, kose7y, kose7z);
        fprintf(output,"Butun noktalari icine alan en kucuk kupun 8. kose noktalari: %f %f %f\n",kose8x, kose8y, kose8z);

        fclose(output);


        break;

           case 4:

            output=fopen("output.nkt","a");
                if(output==NULL){
                    printf("Dosya acilamadi.");
            }

            fprintf(output,"\n4. Secim: \n");

            if(case4_sayac==0){
                    printf("\nYaricap ve xyz noktalarini bosluklu bir sekilde giriniz:");
                    scanf("%f %f %f %f",&kure_yaricap,&kure_merkez_x,&kure_merkez_y,&kure_merkez_z);
                    case4_sayac++;
            }


        for(i=0;i<k;i++)

        {
            if (kure_yaricap>=(sqrt(((b[i].x)-kure_merkez_x)*((b[i].x)-kure_merkez_x))+(((b[i].y)-kure_merkez_y)*((b[i].y)-kure_merkez_y))+(((b[i].z)-kure_merkez_z)*((b[i].z)-kure_merkez_z))))
            {

                kure_nokta_sayisi++;
                printf("%d. indeksteki nokta, koordinatlari:%f %f %f\n",i,b[i].x,b[i].y,b[i].z);
                fprintf(output,"%d. indeksteki nokta, koordinatlari:%f %f %f\n",i,b[i].x,b[i].y,b[i].z);

            }
        }

        printf("Kure icinde ya da uzerinde kalan nokta sayisi:%d",kure_nokta_sayisi);
        fprintf(output,"Kure icinde ya da uzerinde kalan nokta sayisi:%d\n",kure_nokta_sayisi);

        kure_nokta_sayisi=0;

        fclose(output);


        break;

           case 5:

             output=fopen("output.nkt","a");
                if(output==NULL){
                    printf("Dosya acilamadi.");
            }

            fprintf(output,"\n5. Secim: \n");


            for(i=0;i<k;i++){
                for(j=i+1;j<k;j++){

                    uzaklik=0;

                    uzaklik=(sqrt(((b[i].x)-(b[j].x))*((b[i].x)-(b[j].x)))+(((b[i].y)-(b[j].y))*((b[i].y)-(b[j].y)))+(((b[i].z)-(b[j].z))*((b[i].z)-(b[j].z))));
                    toplam_uzaklik+=uzaklik;
                    uzaklik_sayisi++;
                }
        }

            ort_uzaklik=toplam_uzaklik/uzaklik_sayisi;

            printf("Ortalama uzaklik=%f\n",ort_uzaklik);
            fprintf(output,"Ortalama uzaklik=%f\n",ort_uzaklik);


            fclose(output);


            break;

                }
            }

            }

        }

        }


        return 0;

}

