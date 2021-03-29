function on_create()
    subir = false
    cajita = level_get_entities(level)[71]
    vspeed_cajita = 0.0
end
function on_update()
    if subir then
        entity_translate(cajita,0.0,vspeed_cajita*game_get_delta_time(),0.0)
        vspeed_cajita = vspeed_cajita + 4.5
    end
end
function on_collision(other)
    local entity_name = entity_get_name(other)
    if entity_name == "disparo" then
        entity_translate(cajita,1.0,0.0,0.0)
    end
    if entity_name == "resorte" then
        subir = true
        caja_activada = true
        
    end
end
