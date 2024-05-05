package fr.epita.assistants.presentation.rest;

import fr.epita.assistants.presentation.rest.request.ReverseRequest;
import fr.epita.assistants.presentation.rest.response.HelloResponse;
import fr.epita.assistants.presentation.rest.response.ReverseResponse;

import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

@Path("/")
public class Endpoints {


    @Path("hello/{name}")
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response helloWorld(@PathParam("name") String name) {
        if (name == null || name.length() == 0)
            return Response.noContent().build();
        return Response.ok(new HelloResponse(name)).build();
    }

    @Path("reverse")
    @POST
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response reverse(ReverseRequest JsonRequest) {
        if (JsonRequest == null || JsonRequest.getContent() == null || JsonRequest.getContent().length() == 0)
            throw  new BadRequestException();
       return Response.ok(new ReverseResponse(JsonRequest)).build();
    }
}
