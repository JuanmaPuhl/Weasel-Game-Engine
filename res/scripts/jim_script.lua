function on_create()
    print("JIM::OnCreate")
    disparando = false
    status = 1
    count = 1
    walking = false
    level = game_get_current_level()
    entities = level_get_entities(level)
    sprite_idle = game_find_sprite("idle")
    sprite_walking = game_find_sprite("walking")
    sprite_shooting = game_find_sprite("shooting")
    local count = 0
    print("llegue")
    for _ in pairs(entities) do count = count + 1 end
    if count >= 2 then
        entity = entities[1]
        fire = entities[2]
        print("llegue")
        sprite_attribute = entity_get_attribute(entity,"sprite")
        fire_attr = entity_get_attribute(fire, "sprite")
        sprite_fire = attribute_get_sprite(fire_attr)
        col_attr = entity_get_attribute(entity,"color")
        music_component = entity_get_component(entity, "music1");
        print(col_attr)
        sprite_set_transparency(sprite_fire,0.0)
        collision = false
    end
    log_print("Esto es una prueba desde LUA")
end

function on_update()
    if(entity ~= nil and fire ~= nil ) then
        if collision then
            attribute_set_color(col_attr,1.0,0.0,0.0)
        end
        local deltaTime = game_get_delta_time()
        local speed = 96.0
        if is_pressed(KEY_RIGHT) then
            if not walking then
                attribute_set_sprite(sprite_attribute, sprite_walking)
                walking = true
            end
            if status == -1 then
                status = 1
                entity_scale(entity, -1.0,1.0,1.0)
                entity_set_position(fire, 0.0,0.0,0.0)
                entity_scale(fire, -1.0,1.0,1.0)
            end
            entity_translate(entity, speed * deltaTime,0.0,0.0)
        end
        if is_pressed(KEY_LEFT) then
            if not walking then
                attribute_set_sprite(sprite_attribute, sprite_walking)
                walking = true
            end
            if status == 1 then
                status = -1
                entity_scale(entity, -1.0,1.0,1.0)
                entity_set_position(fire, 0.0,0.0,0.0)
                entity_scale(fire, -1.0,1.0,1.0)
            end
            entity_translate(entity,-speed * deltaTime,0.0,0.0)
        end
        if is_pressed(KEY_UP) then
            entity_translate(entity,0.0,speed * deltaTime,0.0)
        end
        if is_pressed(KEY_DOWN) then
            entity_translate(entity,0.0,-speed * deltaTime,0.0)
        end
        if not is_pressed(KEY_RIGHT) and not is_pressed(KEY_LEFT) and not is_pressed(KEY_Z) then
            if walking then
                walking = false
                attribute_set_sprite(sprite_attribute, sprite_idle)
            end
            if disparando then
                print("disparando")
                disparando = false
                attribute_set_sprite(sprite_attribute, sprite_idle)
            end
        end
        if is_pressed(KEY_Z) then
            if not disparando then
                component_music_set_track(music_component, "res/audio/disparo.wav")
                print("la direccion es: ")
                component_music_get_track(music_component)
                component_music_play_track(music_component,true)
                --print(track)
                
                sprite_set_transparency(sprite_fire,1.0)
                disparando = true
                attribute_set_sprite(sprite_attribute, sprite_shooting)
            end
            
            pos = entity_get_position(entity)
            entity_set_position(fire, pos[1] + status * 36.0, pos[2] + 15.0, pos[3])
        else
            disparando = false
            component_music_stop_track(music_component)
            sprite_set_transparency(sprite_fire,0.0)
    
        end
    end
    
    

end

function on_collision(other)
    print("JIM::COLISION")
    collision = true
end