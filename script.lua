-- Create an instance of sprite an call some methods

function on_update()
    print("Estoy en el on_update")
    entity = entity_new()
    entity_get_position(entity)
    entity_translate(entity,2,3,4)
    entity_get_position(entity)
end