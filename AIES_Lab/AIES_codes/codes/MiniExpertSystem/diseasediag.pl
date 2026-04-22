ask(Symptom) :-
    write('Do you have '), write(Symptom), write('? (yes/no): '),
    read(Response),
    Response == yes.

disease(flu) :-
    ask(fever),
    ask(cough),
    ask(body_ache).

disease(cold) :-
    ask(cough),
    ask(sneezing),
    ask(runny_nose).

disease(covid) :-
    ask(fever),
    ask(cough),
    ask(loss_of_taste).

diagnose :-
    (disease(X) ->
        write('You may have: '), write(X), nl
    ;
        write('Disease not identified'), nl
    ).