function Tema2MN(name, k)
	% Functie in care sunt apelate cerintele
	% Intrari:
	% -> name: numele fisierului in care se scriu rezultatele

  %%% ------------------------------------------------------------------------------------------------------------
	%%% Cerinta 1
	%%% ------------------------------------------------------------------------------------------------------------
 	if (fid_aux = fopen('cerinta1.m', 'r')) ~= -1
	    fclose(fid_aux);

      image_in = strcat('in/images/', strcat(name, '.gif'));
      for i = 1 : length(k)
        A_k = cerinta1(image_in, k(i));
      
      image_out = strcat('out/cerinta1_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
      %salvare imagine in fisier
      imwrite(uint8(A_k), image_out);
      end	
	endif
	%%% ------------------------------------------------------------------------------------------------------------
	%%% Cerinta 3
	%%% ------------------------------------------------------------------------------------------------------------
  if (fid_aux = fopen('cerinta3.m', 'r')) ~= -1
	  fclose(fid_aux);

    image_in = strcat('in/images/', strcat(name, '.gif'));
    for i = 1 : length(k)
      A_k = cerinta3(image_in, k(i));
      
      image_out = strcat('out/cerinta3_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
      %salvare imagine in fisier
      imwrite(uint8(A_k), image_out);
    end	
	endif
  
  	%%% ------------------------------------------------------------------------------------------------------------
	%%% Cerinta 4
	%%% ------------------------------------------------------------------------------------------------------------
  if (fid_aux = fopen('cerinta4.m', 'r')) ~= -1
	  fclose(fid_aux);

    image_in = strcat('in/images/', strcat(name, '.gif'));
    for i = 1 : length(k)
      A_k = cerinta4(image_in, k(i));
      
      image_out = strcat('out/cerinta4_', strcat(name, strcat('_', strcat(num2str(k(i)),'.gif'))));
      %salvare imagine in fisier
      imwrite(uint8(A_k), image_out);
    end	
  end  
endfunction