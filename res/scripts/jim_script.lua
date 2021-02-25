function on_create()
    print("JIM::OnCreate")
    disparando = false
    status = 1
    walking = false
    level = game_get_current_level()
    entities = level_get_entities(level)
    entity = entities[1]
end

function on_update()
    if is_pressed(KEY_Q) then
        print("JIM::Presione Q")
    end
    if is_pressed(KEY_RIGHT) then
        entity_translate(entity,1.0,0.0,0.0)
    end
    if is_pressed(KEY_LEFT) then
        entity_translate(entity,-1.0,0.0,0.0)
    end
    if is_pressed(KEY_UP) then
        entity_translate(entity,0.0,1.0,0.0)
    end
    if is_pressed(KEY_DOWN) then
        entity_translate(entity,0.0,-1.0,0.0)
    end

end

function on_collision(other)
    print("JIM::COLISION")
end