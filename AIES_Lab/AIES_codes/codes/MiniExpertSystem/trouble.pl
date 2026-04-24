ask(Problem):-
    write('Do you have issue: '), write(Problem), write('? (yes/no): '),
    read(Response),
    Response == yes.

issue(no_power):-
    ask(no_power),
    ask(no_lights).

issue(slow_coomputer):-
    ask(slow),
    ask(many_programs_running).

issue(no_internet):-
    ask(no_wifi),
    ask(router_off).

issue(overheating):-
    ask(heat),
    ask(fan_noise).

solution(no_power):-
    write('Check power cable or battery'), nl.
solution(slow_coomputer):-
    write('Close unused programs or restart system'), nl.
solution(no_internet):-
    write('Restart router or check connection'), nl.
solution(overheating):-
    write('Clean fan or improve ventilation'), nl.

troubleshoot:-
    (issue(X) ->
        write('Problelm identified: '), write(X), nl,
        solution(X)
    ;
        write('Issue not identified'), nl
    ).