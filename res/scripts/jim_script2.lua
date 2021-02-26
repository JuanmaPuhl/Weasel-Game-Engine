function on_create()
    level = game_get_current_level()
    entities = level_get_entities(level)
    jim = entities[1]
    colorattr = entity_get_attribute(jim,"color")
    colorR = 1.0
    colorG = 0.0
    colorB = 0.0
    estado = 1
end

function on_update()
    if colorR >= 1.0 and colorG <= 0.1 and colorB <= 0.0 then
        estado = 1
    elseif colorR >= 1.0 and colorG >= 1.0 and colorB <= 0.0 then
        estado = 2
    elseif colorR <= 0.0 and colorG >= 1.0 and colorB <= 0.0 then
        estado = 3
    elseif colorR <= 0.0 and colorG >= 1.0 and colorB >= 1.0 then
        estado = 4
    elseif colorR <= 0.0 and colorG <= 0.0 and colorB >= 1.0 then
        estado = 5
    elseif colorR >= 1.0 and colorG <= 0.0 and colorB >= 1.0 then
        estado = 6
    end
    if estado == 1 then
        colorG = colorG + game_get_delta_time()
        if colorG >= 1.0 then
            colorG = 1.0
        end
    end
    if estado == 2 then
        colorR = colorR - game_get_delta_time()
        if colorR <= 0.0 then
            colorR = 0.0
        end
    end
    if estado == 3 then
        colorB = colorB + game_get_delta_time()
        if colorB >= 1.0 then
            colorB = 1.0
        end
    end
    if estado == 4 then
        colorG = colorG - game_get_delta_time()
        if colorG <= 0.0 then
            colorG = 0.0
        end
    end
    if estado == 5 then
        colorR = colorR + game_get_delta_time()
        if colorR >= 1.0 then
            colorR = 1.0
        end
    end
    if estado == 6 then
        colorB = colorB - game_get_delta_time()
        if colorB <= 0.0 then
            colorB = 0.0
        end
    end
    attribute_set_color(colorattr,colorR,colorG,colorB)
end

