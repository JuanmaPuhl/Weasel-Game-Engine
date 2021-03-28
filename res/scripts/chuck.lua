function on_create()
    chuck_being_hit = true
    chuck_count_hits = 45
    chuck_life = 3
    chuck = level_get_entities(level)[64]
    chuck_sprite_attribute = entity_get_attribute(chuck,"sprite")
    chuck_music_component = entity_get_component(chuck,"music")
    chuck_damage_sprite = game_find_sprite("chuck_damage")
    chuck_burping_sprite = game_find_sprite("chuck_burp")
    chuck_izq_sprite = game_find_sprite("chuck_izq")
    chuck_der_sprite = game_find_sprite("chuck_der")
    chuck_vomitando = false
    chuck_status = -1
    chuck_vomitando1 = false
end
function on_update()
    --Una vez que recibe daño
    if chuck_being_hit then
        --Tengo que esperar a que termine la animacion de daño
        if not chuck_vomitando then
            local chuck_current_sprite = attribute_get_sprite(chuck_sprite_attribute)
            local chuck_current_sprite_index = sprite_get_current_image(chuck_current_sprite)
            print("index")
            print(chuck_current_sprite_index)
            if chuck_current_sprite_index == 2 then
                chuck_vomitando = true
            end
        else
            --Tengo que vomitar 7 pescados
            
            if not chuck_vomitando1 then
                local current_chuck_position = entity_get_position(chuck)
                print("posicion")
                print(current_chuck_position[1])
                print(current_chuck_position[2])
                print(current_chuck_position[3])
                --local cx = current_chuck_position[1]
                --local cy = current_chuck_position[2]
                --local pescado_1 = chuck_entities[65]
                --entity_set_position(pescado_1,cx,cy,0.0)
                chuck_vomitando1 = true
            else
                --entity_translate(pescado_1, -4.0/3.0,-4.0,0.0)
                --print("vomitando")
            end

        end
        

    end
end
function on_collision()
    local entity_name = entity_get_name(other)
    if entity_name == "caja" then
        if not chuck_being_hit then
            
            if chuck_count_hits == 0 then
                --component_music_play_track(bird_music_component,false)
                chuck_being_hit = true
                attribute_set_sprite(chuck_sprite_attribute,chuck_damage_sprite)
                chuck_life = chuck_life -1
            else
                chuck_count_hits = chuck_count_hits-1
            end
        end
    end
end