ask(Question) :-
    write('Do you like '), write(Question), write('? (yes/no): '),
    read(Response),
    Response == yes.

career(engineer):-
    ask(math),
    ask(problem_solving),
    ask(technology).

career(doctor):-
    ask(biology),
    ask(helping_people),
    ask(patience).

career(artist):-
    ask(teaching),
    ask(communication),
    ask(helping_others).

suggest:-
    (career(X) ->
        write('Suggested career: '), write(X), nl
    ;
        write('No suitable career found'), nl
    ).
